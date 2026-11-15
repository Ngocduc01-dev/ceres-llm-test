# Kế hoạch: Sinh unit test tự động bằng LLM cho Ceres Solver (CFT – C2)

## 1. Phạm vi bài toán

| Mục | Nội dung |
|---|---|
| Project | [ceres-solver](https://github.com/ceres-solver/ceres-solver) (C++17, ~100k LOC) |
| Loại test | Chỉ unit test, không làm test tích hợp |
| Kỹ thuật | Kiểm thử dòng điều khiển (CFT), không có đặc tả nên không có EO, không dùng biên / phân hoạch / bảng quyết định |
| Tiêu chí phủ | **C2 – phủ nhánh** (mục tiêu chính). C3 chỉ đo thêm nếu tiện (GCC 14 `-fcondition-coverage`) |
| Sinh dữ liệu | Ngẫu nhiên + LLM định hướng, **không quan tâm PASS/FAIL** |
| Đầu ra | Bộ test cho **tất cả unit** + báo cáo độ phủ + phân loại unit/nhánh không xử lý được |

**Lý do chọn C2 thay vì C3:** Ceres dùng nhiều template và Eigen; điều kiện chủ yếu là so sánh số thực trên ma trận; có rất nhiều `CHECK`/`DCHECK` (nhánh False làm dừng chương trình). C3 tốn công nhiều mà số liệu không có ý nghĩa thêm.

**Những phần bỏ so với khung tổng quát:** lọc bớt target (phải làm tất cả), oracle / assertion đúng (không có EO), mutation testing, giá trị biên theo đặc tả.

**Các quyết định đã chốt:**

| Vấn đề | Quyết định | Chi tiết |
|---|---|---|
| Phiên bản Ceres | Release **2.2.0** | `docs/baseline-comparison.md` |
| Tiêu chí phủ | **C2** (phủ nhánh) | mục 1 |
| Đơn vị prompt | **1 prompt = 1 unit** (1540 prompt, chạy bằng script) | Phase 5 |
| CFG | **Tool dựng** – Clang Static Analyzer `debug.DumpCFG` + script lọc nhiễu, gắn số dòng; LLM đọc và chuẩn hoá | Phase 4 |
| Prompt | 1 prompt chung 7 mục | `prompts/master_prompt.md`, `docs/prompt-design.md` |
| EO | Không có – không viết assertion so sánh kết quả | mục 1 |
| Input | Chọn ngẫu nhiên trong miền thoả điều kiện đường đi, seed cố định | Phase 5 |
| Vòng lặp | 2 loại: **có cận** (0, 1, 2, m, n−1, n, n+1) / **không có cận** (0, 1, 2 + mỗi lối thoát); cận là biến → chọn ngẫu nhiên | `prompts/master_prompt.md` mục 2.3 |
| Lưu kết quả | Mỗi unit 1 thư mục `units/<id>/`: `prompt.md`, `cfg.txt` (bản đã lọc), `response.md` (bảng nhánh, test path, test case), `<id>_test.cc` | Phase 5 |
| Không làm | Fuzzing (OSS-Fuzz-gen) – quá công | `docs/survey-llm-testgen.md` |

---

## 2. Tổng quan pipeline

```
Phase 0  Build + parse
   │
Phase 1  Code graph ──► Phase 2  Liệt kê & phân loại unit
                              │
              ┌───────────────┘
              ▼
Phase 3  Gom context ─► Phase 4  CFG (Clang) ─► Phase 5  Sinh test (1 prompt/unit)
                                                          ▲        │
                                                          │        ▼
                                          nhánh chưa phủ  └── Phase 6  Compile / chạy / đo phủ
                                                                   │
                                                          Phase 7  Hậu xử lý
                                                                   │
                                                          Phase 8  Chạy hàng loạt + báo cáo
```

---

## 3. Chi tiết từng phase

### Phase 0 – Chuẩn bị môi trường, build và parse
**Phụ trách:** A (build), B (parse)

**Mục tiêu:** build được Ceres có bật coverage, parse được toàn bộ source.

**Các bước:**
1. Dựng **Docker image** dùng chung: GCC 14, CMake, Ninja, Eigen3, gcovr, lcov, Python 3 + `libclang`, glog, gflags (googletest có sẵn trong `internal/ceres/` của Ceres 2.2.0).
2. Build Ceres cấu hình tối giản (kiểm tra lại tên option trong `CMakeLists.txt` theo version):
   ```bash
   cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS="--coverage -O0" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DBUILD_EXAMPLES=OFF -DBUILD_BENCHMARKS=OFF -DUSE_CUDA=OFF -DSUITESPARSE=OFF -DLAPACK=OFF -DEIGENMETIS=OFF -DSCHUR_SPECIALIZATIONS=OFF -DMINIGLOG=OFF
   ```
3. Chạy test có sẵn (`ctest`) → `gcovr` → lấy **độ phủ baseline** (C1, C2).
4. Kiểm tra `compile_commands.json` đã sinh (libclang cần file này để parse đúng).
5. Parse thử toàn bộ `internal/ceres/*.cc`, `include/ceres/*.h` bằng libclang, đếm file lỗi.

**Đầu ra:** `build.sh`, `coverage.sh`, báo cáo baseline, danh sách file parse được / lỗi.

**Lưu ý:**
- `internal/ceres/generated/` là code sinh tự động → loại khỏi phạm vi (hoặc gộp thành 1 unit), ghi rõ trong báo cáo.
- Nhóm chốt **Ceres release 2.2.0** (dùng glog thật, không dùng miniglog – Phase 6 cần hook hàm xử lý lỗi của glog).

---

### Phase 1 – Xây code graph
**Phụ trách:** B

**Mục tiêu:** biết mỗi unit gọi hàm nào, dùng kiểu nào, cần include gì.

**Các bước:**
1. Duyệt AST bằng `clang.cindex` với cờ compile từ `compile_commands.json`.
2. Trích các loại cạnh:
   - **gọi hàm** – `CALL_EXPR` → `.referenced`
   - **dùng kiểu** – kiểu tham số, giá trị trả về, biến cục bộ
   - **kế thừa** – `CXX_BASE_SPECIFIER`
   - **include** – file include file
   - **thuộc về** – method thuộc class
3. Lưu vào **SQLite**: bảng `nodes` (id, tên, loại, file, dòng đầu–cuối), `edges` (from, to, loại).
4. Viết `get_neighbors(unit_id, hops=2)` cho Phase 3.

**Đầu ra:** `graph.db`, `graph_query.py`.

**Lưu ý:** template và lời gọi virtual có thể không resolve hết → chấp nhận, ghi lại số cạnh không resolve được.

---

### Phase 2 – Liệt kê và phân loại unit
**Phụ trách:** B

**Mục tiêu:** danh sách **toàn bộ unit**, có mức độ khó và thứ tự xử lý.

**Các bước:**
1. **Định nghĩa unit:** hàm/method có thân trong `internal/ceres/` và `include/ceres/`. Loại `*_test.cc`, code generated, hàm chỉ khai báo, pure virtual.
2. Với mỗi unit ghi: signature, file, dòng, số nhánh (`if`, `for`, `while`, `switch/case`, `?:`, `&&`, `||`), cyclomatic complexity.
3. Phân loại:

   | Mức | Đặc điểm | Ví dụ |
   |---|---|---|
   | Dễ | Tham số là số, `bool`, con trỏ mảng | hàm toán học tiện ích |
   | Trung bình | Eigen, `std::vector`, struct nhỏ | thao tác vector/ma trận |
   | Khó | Cần `Problem`, `CostFunction`, `LinearSolver`, sparse matrix, thread | các bước của solver |
   | Không gọi trực tiếp | `static`, anonymous namespace, `private` | hàm nội bộ |

4. **Sắp thứ tự** bằng topological sort trên call graph: unit lá trước, unit cấp cao sau.
5. Template trong header: chọn kiểu instantiate (`double`, `Jet` nếu cần), ghi vào JSON.

**Đầu ra:** `units.json`
```json
{ "id": "u0421", "name": "ceres::internal::Foo::Bar", "file": "internal/ceres/foo.cc",
  "lines": [120, 168], "signature": "...", "branches": 6, "level": "trung_binh",
  "callable": "public", "template_args": null, "order": 37 }
```

---

### Phase 3 – Gom context cho từng unit
**Phụ trách:** C

**Mục tiêu:** gói context đủ để LLM viết test **compile được**, trong giới hạn token.

**Gói context gồm:**
1. Code của unit.
2. Khai báo class chứa unit (field, constructor, method liên quan).
3. **Signature** các callee cách 1–2 bước trên graph (không cần thân hàm).
4. Định nghĩa các kiểu trong tham số / giá trị trả về.
5. **Danh sách `#include` cần có** (từ include graph) – nguyên nhân lỗi compile phổ biến nhất.
6. **Test mẫu**: nếu có `foo_test.cc` tương ứng thì trích 1–2 test để LLM bắt chước cách khởi tạo object.
7. **Helper tạo input** do E viết + helper có sẵn trong repo (vd. `linear_least_squares_problems.h` – kiểm tra lại).
8. **Cách gọi** nếu unit là `static` / `private` / anonymous namespace (xem Phase 5).

**Giới hạn token:** trần ~6–8k token. Vượt trần thì bỏ theo thứ tự: test mẫu → callee cách 2 bước → kiểu ít quan trọng.

**Đầu ra:** `data/context/<id>.txt`, `scripts/build_context.py`.

**Trạng thái: ✅ xong** (1540 context, trung bình ~2.2k token). Lỗi cần sửa trước Phase 5 (từ kiểm tra 1540 file):
1. 80 unit `static`: `#include "internal/ceres/x.cc"` sai đường dẫn → phải là `#include "ceres/x.cc"`.
2. 332 unit (25 class dài > 120 dòng): khai báo class bị cắt → thay bằng **bản tóm tắt class** (constructor, signature method, biến thành viên) lấy từ `graph.db`.
3. Thư mục `helpers/` chưa có → 396 unit "khó" thiếu hàm tạo input.
4. `#define private public` phải đặt sau include gtest/thư viện chuẩn/Eigen (đã ghi vào prompt chung).

---

### Phase 4 – Lập kế hoạch test theo C2
**Phụ trách:** C

**Mục tiêu:** mỗi unit có **CFG dựng bằng tool** (bản đã lọc nhiễu) để đưa vào prompt.

**Đã chốt:** CFG do **Clang Static Analyzer** dựng (`debug.DumpCFG`, có sẵn trong clang-18 của Docker), **không** để LLM tự dựng và **không** tự viết thuật toán dựng CFG.
- Lý do: Clang hiểu đúng C++ (macro đã bung, `#if` theo đúng cờ build, `switch`/`break`/`continue`/`try`); LLM đọc source thô sẽ vẽ cả code trong `#if` bị tắt; mẫu số C2 cố định giữa các lần chạy.
- CFG là **trong một hàm** (intra-procedural): mỗi unit 1 CFG, không phụ thuộc hàm khác → dựng song song, không cần thứ tự.

**Các bước (script `scripts/build_cfg.py`):**

| Mức | Việc | Trạng thái |
|---|---|---|
| 1. Chạy + lọc (bắt buộc) | Với mỗi unit: lấy cờ compile từ `compile_commands.json`, chạy `clang++ --analyze -Xclang -analyzer-checker=debug.DumpCFG` cho đúng hàm (`-analyze-function`), tắt khối ngầm bằng `-analyzer-config`, bỏ dòng `ImplicitCastExpr` → `data/cfg/<id>.txt` | cần làm |
| 2. Gắn số dòng (nên có) | Gắn `@L<số dòng>` cho khối quyết định (`T: if/for/while/...`), đối chiếu với node `IF_STMT`/`FOR_STMT`… trong AST Phase 1 | cần làm |
| 3. JSON + gom `&&`/`||` + Mermaid + V(G) | Chỉ làm nếu chạy thử thấy LLM đọc text CFG sai nhiều | dự phòng |

- Unit nào Clang không dựng được CFG → để trống, prompt tự chuyển sang "LLM tự dựng CFG".
- **Cần thử trước:** cách `-analyze-function` nhận tên method/overload/template (có thể phải ghi kèm kiểu tham số).
- Chỉ lưu **bản đã lọc** (không lưu output thô của Clang).

**Đầu ra:** `units/<id>/cfg.txt`.

---

### Phase 5 – Sinh code test
**Phụ trách:** D

**Mục tiêu:** mỗi unit có một file GoogleTest.

**Quy ước:**
- Mỗi unit một file `units/<id>/<id>_test.cc`.
- Mỗi test case là một `TEST(...)`, ngay trên có 1 dòng comment ghi test path.
- **Không assert theo EO** – chỉ gọi hàm, có thể in kết quả thực tế.
- Giá trị ngẫu nhiên dùng seed cố định (chạy lại ra đúng giá trị cũ).

**Cách gọi unit khó:**

| Tình huống | Cách xử lý |
|---|---|
| `static` / anonymous namespace | `#include "foo.cc"` thẳng vào file test |
| Method `private` | Gọi qua method public, hoặc `#define private public` trước include (hack – ghi rõ trong báo cáo) |
| Template | Chọn kiểu cụ thể – gợi ý ở dòng "Ghi chú" của CFG (kiểu Ceres đã dùng thật) |
| Dependency nặng | Class con giả lập / stub (vd. `CostFunction` đơn giản) |

**Đã chốt:**
- **1 prompt = 1 unit** (1 hàm hoặc 1 method) → **1540 prompt**, chạy bằng script. Theo ý thầy ("không có unit nào lớn đến mức AI không xử lý hết", "chỉ làm unit testing"), theo cách Google/IBM/Huawei làm (khảo sát: `docs/survey-llm-testgen.md`), và vì CFT/C2 tính trên từng unit.
- **Prompt chung:** [`prompts/master_prompt.md`](../prompts/master_prompt.md), giải thích bố cục: [`docs/prompt-design.md`](prompt-design.md). 7 mục: Vai trò → Khái niệm (CFG, **C2 + công thức**, vòng lặp có cận / không có cận, test path, path condition, nhánh bất khả thi, `CHECK`) → Đầu vào (thông tin + mã nguồn của unit, **CFG Clang + cách đọc**, cách gọi unit) → Yêu cầu bộ test → Các bước → Kết quả (test paths, test case, nhánh không test + C2 dự kiến, 1 file GoogleTest) → Lưu ý.
- **Không có EO:** không viết assertion so sánh kết quả; chỉ cần đi qua nhánh.
- **Input:** giải điều kiện đường đi → miền giá trị → **chọn ngẫu nhiên trong miền**, seed cố định.
- **Vòng lặp:** có cận → 0, 1, 2, m, n−1, n, n+1 lần; không có cận → 0, 1, 2 lần + mỗi lối thoát 1 test; cận là biến → chọn ngẫu nhiên.
- **Model:** Claude Sonnet 5.5, effort low, **gọi qua Claude Code CLI** (dùng gói Claude sẵn có, không cần API key):
  ```bash
  claude -p --model claude-sonnet-5-5 --effort low --tools "" --output-format json --no-session-persistence \
    --system-prompt "<1 câu vai trò>" --setting-sources "" --strict-mcp-config < units/<id>/prompt.md
  ```
  - `--tools ""`: tắt mọi tool → model chỉ đọc prompt và trả lời (đúng là "1 lần gọi LLM").
  - `--system-prompt`, `--setting-sources ""`, `--strict-mcp-config`: không gửi kèm system prompt mặc định của Claude Code, CLAUDE.md, memory, MCP của máy → model chỉ nhận đúng `prompt.md`. Smoke test lần 1 chưa có các cờ này: mỗi lần gọi tốn ~65k token đầu vào; có cờ: ~1k + prompt.
  - Chạy **tuần tự**, gặp giới hạn lượt dùng thì **dừng**; lần sau chạy lại sẽ **bỏ qua unit đã có `response.md`** → gọi được đến đâu thì lưu đến đó.
  - Cần đăng nhập CLI một lần trong terminal (`claude` rồi `/login`).
- **Thứ tự chạy:** 20 unit smoke test → toàn bộ theo `topo_level` từ 0 lên.

**Script (đã viết):**

| Script | Chạy bằng | Việc |
|---|---|---|
| `scripts/init_units.py` | Python 3 (WSL/Docker) | tạo `units/<id>/info.json` cho 1540 unit ✅ đã chạy |
| `scripts/render_prompt.py` | Python 3 | `prompts/master_prompt.md` + `data/context/<id>.txt` + mã nguồn (đánh số dòng) + `units/<id>/cfg.txt` → `units/<id>/prompt.md`. Chưa có `cfg.txt` thì prompt tự chuyển sang "LLM tự dựng CFG" |
| `scripts/generate.mjs` | Node (Windows, cùng máy có `claude`) | gọi Claude Code CLI cho từng prompt (thứ tự `topo_level`) → `response.md` + `<id>_test.cc`; bỏ qua unit đã có `response.md`; gặp lỗi đăng nhập / hết lượt thì dừng; log `logs/raw/generate.log` |

```bash
tar -xzf data_phase3.tar.gz data/context            # context Phase 3 (1 lần)
python3 scripts/render_prompt.py --smoke            # ghép prompt 20 unit smoke test (sau Phase 4: chạy lại để có CFG)
node scripts/generate.mjs --smoke                   # gọi Claude cho 20 unit
node scripts/generate.mjs --limit 100               # các lần sau: 100 unit tiếp theo, chạy đến đâu lưu đến đó
```

**Đầu ra – mỗi unit 1 thư mục (tài liệu của từng prompt):**
```
units/u0553/
├── info.json       # thông tin unit (tên, tham số, class, file, dòng, cách gọi…)
├── source.cc       # mã nguồn của unit, trích từ file gốc (chỉ để xem, không compile)
├── cfg.txt         # Phase 4 – CFG Clang đã làm gọn (không có nếu Clang không dựng được -> LLM tự dựng)
├── prompt.md       # đúng prompt đã gửi
├── response.md     # nguyên văn câu trả lời: test path, test case, nhánh không test + C2 dự kiến, code
└── u0553_test.cc   # file test tách từ response
```

---

### Phase 6 – Compile, chạy và vòng lặp phủ nhánh
**Phụ trách:** D (compile + sửa), A (đo phủ)

**Chia 2 đợt:**
- **Tuần này:** chạy **1 lượt** bước 1–4 (compile, chạy, đo phủ), **chưa sửa gì**; thống kê lỗi theo loại (thiếu include, sai kiểu, không gọi được private, crash, timeout…). Đây là đầu vào cho tuần 12–13.
- **Tuần 12–13:** sửa lỗi – **lỗi prompt** (lặp lại nhiều unit → sửa khuôn/context, sinh lại cả nhóm) và **lỗi test** (riêng từng file → vòng sửa compile tối đa 3 lần, vòng phủ thêm nhánh tối đa 3–5 vòng). Cảnh báo từ nghiên cứu SAP HANA: sửa nhiều vòng → LLM có xu hướng viết test rỗng để compile được → kiểm tra test có thật sự gọi unit.

**Các bước:**
1. **Compile:** target `gen_tests` trong CMake, link `ceres` bản coverage, dùng `ccache`.
   - Lỗi → gửi lỗi (cắt ngắn) + code cho LLM sửa, **tối đa 3 lần**.
   - Vẫn lỗi → `compile_fail` + loại lỗi (thiếu include, sai kiểu, sai template…).
2. **Chạy:** từng unit riêng (`--gtest_filter=Gen_<id>.*`), **timeout ~10s**. PASS / FAIL / exception đều chấp nhận, chỉ ghi lại.
3. **Bẫy: crash làm mất dữ liệu gcov.** `CHECK` sai → `abort()` → gcov không ghi `.gcda`. Xử lý:
   - `google::InstallFailureFunction(...)` với hàm gọi `__gcov_dump()` rồi thoát.
   - Handler cho `SIGSEGV`, `SIGABRT`, `SIGTERM` (timeout) cũng gọi `__gcov_dump()`.
4. **Đo phủ từng unit:** xóa `.gcda` → chạy test của unit → `gcovr --json --exclude-throw-branches --exclude-unreachable-branches` → lọc theo dòng của unit.
5. **Vòng lặp:** nhánh chưa phủ (dòng, điều kiện, thiếu True/False) → quay lại Phase 5 sinh thêm. **Tối đa 3–5 vòng**, dừng sớm nếu phủ đủ hoặc một vòng không tăng nhánh nào.

**Đầu ra:** `results/<id>.json`
```json
{ "id": "u0421", "status": "ok", "compile_tries": 2, "rounds": 3,
  "branches_total": 12, "branches_covered": 10,
  "run": {"pass": 5, "fail": 2, "crash": 1, "timeout": 0},
  "uncovered": [{"line": 150, "cond": "x > tol", "missing": "false"}] }
```
`status`: `ok` | `compile_fail` | `run_fail` | `skipped`.

---

### Phase 7 – Hậu xử lý
**Phụ trách:** E

**Các bước:**
1. **Bỏ test thừa:** greedy – giữ test phủ nhiều nhánh mới nhất trước, loại test không tăng độ phủ.
2. **Kiểm tra ổn định:** chạy lại toàn bộ 2–3 lần, độ phủ phải giống nhau.
3. **Phân loại nhánh không phủ được:**
   - infeasible / code chết (kiểm tra tay một mẫu hoặc LLM đánh giá rồi kiểm tra lại)
   - nhánh False của `CHECK` / `DCHECK`
   - do hạn chế của nhóm (không tạo được input, không gọi được unit)
4. **Phân loại unit thất bại** theo nguyên nhân, kèm số lượng (xem mục 4).
5. `clang-format` toàn bộ file sinh ra.

**Đầu ra:** `gen_tests/` cuối cùng, `failures.csv`.

---

### Phase 8 – Điều phối, chạy hàng loạt, báo cáo
**Phụ trách:** E

**Các bước:**
1. `run_all.py`: đọc `units.json` theo thứ tự, chạy P3 → P6 cho từng unit, song song N worker (giới hạn theo CPU).
2. **Resume:** unit đã có `results/<id>.json` thì bỏ qua.
3. **Cache phản hồi LLM** theo hash prompt.
4. **Log** từng unit: prompt, phản hồi, lỗi compile, số liệu phủ (làm bằng chứng khi trình bày).
5. **Đo lần cuối:** xóa toàn bộ `.gcda`, chạy cả bộ test sinh ra một lần, đo toàn project.
6. **Bảng số liệu:**

   | Chỉ số | Giá trị |
   |---|---|
   | Tổng số unit / số unit trong phạm vi | |
   | % sinh được, % compile được, % chạy được | |
   | C1, C2 – test có sẵn (baseline) | |
   | C1, C2 – test sinh ra | |
   | C1, C2 – gộp test có sẵn + sinh ra | |
   | Số nhánh infeasible / `CHECK` / không phủ được | |
   | Thời gian chạy, chi phí token | |

7. **Story line hàng tuần** (mục 6).
8. *(Tùy chọn)* Thử KLEE trên vài unit dễ để so sánh. Không chạy được (Eigen, C++17) thì ghi lý do – cũng là kết quả.

---

## 4. Xử lý khi không sinh được / không chạy được

| Tình huống | Cách xử lý |
|---|---|
| Project không build được | Sửa môi trường (Docker, đúng version); tắt bớt dependency tùy chọn |
| Unit cần DB / file / thread / solver nặng | Stub, class giả lập, helper tạo input |
| Constructor phức tạp, object lồng nhau | LLM sinh code khởi tạo, dùng helper / test mẫu có sẵn |
| `static`, `private`, anonymous namespace | `#include "foo.cc"`, gọi qua hàm public, `#define private public` |
| Test không compile sau 3 lần sửa | Ghi `compile_fail` + loại lỗi |
| Treo / vòng lặp vô hạn | Timeout + `__gcov_dump()` trong signal handler |
| Crash / `CHECK` fail / exception | **Vẫn tính phủ** (đã hook `__gcov_dump`) |
| Nhánh infeasible | Ghi infeasible, không tính vào mẫu số |
| Template không instantiate được | Ghi `skipped` + lý do |

Nguyên tắc: **LLM → random → đánh dấu thất bại có lý do.** Unit nào cũng phải có kết quả.

---

## 5. Phân công và lịch

**Trạng thái:** Phase 0 ✅ · Phase 1 ✅ · Phase 2 ✅ · Phase 3 ✅ (còn 4 lỗi cần sửa) · **Phase 4 ✅** (1491/1540 unit có CFG – `logs/phase4-log.md`) · Phase 5: đã sinh test 270/1540 unit (20 smoke + 250 đầu) · Phase 6 lượt 1: 253/270 compile được (`logs/phase6-log.md`) · Phase 7–8 ⏳

**Tuần này – mục tiêu: sinh được test cho toàn bộ 1540 unit và chạy 1 lượt**

| Người | Việc | Đầu ra |
|---|---|---|
| A | ~~Phase 4: `build_cfg.py`~~ ✅ xong; tiếp: script Phase 6 (compile, chạy, đo phủ từng unit) | `units/<id>/cfg.txt` ✅ |
| B | Phase 3: sửa 4 lỗi context (include `.cc`, tóm tắt class, …) | `data/context/` |
| C | Phase 5: `render_prompt.py` điền `prompts/master_prompt.md`; soát tay 10 prompt | `units/<id>/prompt.md` |
| D | Phase 5: `generate.py` (Claude Code CLI, Sonnet 5.5 low, chạy tiếp được, tách code) | `units/<id>/response.md`, `<id>_test.cc` |
| E | Thư viện `helpers/` tạo input cho unit "khó" (`Problem`, `ParameterBlock`, `BlockSparseMatrix`…); Phase 6 lượt 1: compile/chạy/đo phủ + thống kê lỗi | `helpers/`, `results/` |

**Mốc:** chạy trọn P3 → P6 trên **20 unit smoke test** trước; ổn mới chạy cả 1540 unit.

**Tuần 12–13:** sửa lỗi prompt + lỗi test (Phase 6 vòng lặp), hậu xử lý (Phase 7), báo cáo (Phase 8).

**Cần làm:** đăng nhập Claude Code CLI trên máy chạy `generate.py`.

---

## 6. Mẫu story line hàng tuần

1. **Đã làm:** …
2. **Số liệu:** số unit xử lý / tổng; % compile; % chạy; C1, C2 (so với baseline).
3. **Vấn đề gặp phải:** …
4. **Cách xử lý:** … (tham chiếu mục 4)
5. **Tuần tới:** …

---

## 7. Cấu trúc thư mục đề xuất

```
project/
├── docker/                 # Dockerfile
├── ceres-solver/           # submodule
├── scripts/
│   ├── build.sh
│   ├── coverage.sh
│   ├── parse_ast.py        # P0, P1
│   ├── graph_query.py      # P1
│   ├── list_units.py       # P2
│   ├── build_context.py    # P3
│   ├── plan_branches.py    # P4
│   ├── random_gen.py       # P4
│   ├── generate.py         # P5
│   ├── compile_run.py      # P6
│   ├── postprocess.py      # P7
│   └── run_all.py          # P8
├── helpers/                # helper tạo input Ceres, gcov hook
├── data/
│   ├── graph.db
│   ├── units.json
│   ├── context/
│   ├── plan/
│   └── results/
├── gen_tests/              # test sinh ra
├── logs/
└── report/
```

---

## 8. Tài liệu tham khảo

### 8.1. Sinh unit test bằng LLM

Khảo sát cách các công ty (Meta, Google, IBM, Huawei, Tencent, SAP) làm và cách áp dụng cho bài tập: [`docs/survey-llm-testgen.md`](survey-llm-testgen.md).

| Tài liệu | Nội dung chính | Dùng cho phase |
|---|---|---|
| Wang et al., *Software Testing with Large Language Models: Survey, Landscape, and Vision*, IEEE TSE 2024 – [arXiv:2307.07221](https://arxiv.org/abs/2307.07221) | Tổng quan 102 nghiên cứu dùng LLM cho kiểm thử; các thách thức: độ phủ, test oracle | Tổng quan, phần mở đầu báo cáo |
| Schäfer et al., *An Empirical Evaluation of Using Large Language Models for Automated Unit Test Generation* (TestPilot), IEEE TSE 2024 – [arXiv:2302.06527](https://arxiv.org/abs/2302.06527) | Prompt gồm signature + thân hàm + ví dụ sử dụng; test lỗi thì gửi lại lỗi cho LLM sửa; đo statement/branch coverage | 3, 5, 6 |
| Chen et al., *ChatUniTest: A Framework for LLM-Based Test Generation*, FSE 2024 demo – [arXiv:2305.04764](https://arxiv.org/abs/2305.04764) | "Adaptive focal context": chọn context đưa vào prompt theo giới hạn token; vòng sinh → kiểm tra → sửa | 3, 5, 6 |
| Wang et al., *HITS: High-coverage LLM-based Unit Test Generation via Method Slicing*, 2024 – [arXiv:2408.11324](https://arxiv.org/abs/2408.11324) | Hàm phức tạp (cyclomatic cao) chia thành nhiều đoạn, sinh test từng đoạn → tăng phủ nhánh | 4, 5 (nhóm C, D) |
| Pizzorno & Berger, *CoverUp: Coverage-Guided LLM-Based Test Generation* – [arXiv:2403.16218](https://arxiv.org/abs/2403.16218) | Dùng dữ liệu độ phủ chỉ cho LLM các dòng/nhánh chưa phủ, lặp hội thoại → tăng phủ | 4, 6 |
| Alshahwan et al., *Automated Unit Test Improvement using Large Language Models at Meta* (TestGen-LLM), FSE 2024 – [arXiv:2402.09171](https://arxiv.org/abs/2402.09171) | Lọc test sinh ra: phải build được, chạy ổn định, tăng độ phủ mới giữ lại | 6, 7 |
| Bhargava et al., *CPP-UT-Bench: Can LLMs Write Complex Unit Tests in C++?* – [arXiv:2412.02735](https://arxiv.org/abs/2412.02735) | Benchmark sinh unit test C++ (14 dự án mã nguồn mở) | Đối chiếu kết quả với C++ |
| [qodo-ai/qodo-cover](https://github.com/qodo-ai/qodo-cover) (trước là Cover-Agent) | Mã nguồn mở cài đặt lại TestGen-LLM: vòng sinh → chạy → đo phủ → lọc | Tham khảo cài đặt Phase 5–7 |

### 8.2. GCC, gcov, gcovr (Phase 0, đo độ phủ)

| Tài liệu | Nội dung |
|---|---|
| [GCC – Gcov](https://gcc.gnu.org/onlinedocs/gcc/Gcov.html) | Giới thiệu gcov, cách đọc kết quả |
| [GCC – Invoking Gcov](https://gcc.gnu.org/onlinedocs/gcc/Invoking-Gcov.html) | Tuỳ chọn `-b` (nhánh), `--conditions` (điều kiện con, cần `-fcondition-coverage`) |
| [GCC – Instrumentation Options](https://gcc.gnu.org/onlinedocs/gcc/Instrumentation-Options.html) | Cờ `--coverage`, `-fprofile-update=atomic`, `-fcondition-coverage` |
| [gcovr User Guide](https://gcovr.com/en/stable/) | Lọc file (`--filter`, `--exclude`), bỏ nhánh exception (`--exclude-throw-branches`), xuất HTML |
| [gcovr – JSON Output](https://gcovr.com/en/stable/output/json.html) | Định dạng `coverage.json` (từng nhánh) và `--json-summary` – Phase 4/6 đọc file này |

### 8.3. CMake, libclang (Phase 0–2)

| Tài liệu | Nội dung |
|---|---|
| [Ceres Solver – Installation](http://ceres-solver.org/installation.html) | Dependency và option CMake của Ceres |
| [CMake – CMAKE_EXPORT_COMPILE_COMMANDS](https://cmake.org/cmake/help/latest/variable/CMAKE_EXPORT_COMPILE_COMMANDS.html) | Sinh `compile_commands.json` |
| [Clang – JSON Compilation Database](https://clang.llvm.org/docs/JSONCompilationDatabase.html) | Định dạng `compile_commands.json` |
| [Clang – libclang](https://clang.llvm.org/docs/LibClang.html) và [C API (Doxygen)](https://clang.llvm.org/doxygen/group__CINDEX.html) | API chính thức: cursor, kind, type, token |
| [`clang/bindings/python/clang/cindex.py`](https://github.com/llvm/llvm-project/blob/main/clang/bindings/python/clang/cindex.py) | Mã nguồn binding Python – tài liệu đầy đủ nhất cho `clang.cindex` |
| Eli Bendersky, [Parsing C++ in Python with Clang](https://eli.thegreenplace.net/2011/07/03/parsing-c-in-python-with-clang) | Hướng dẫn nhập môn: tạo `Index`, parse, duyệt cây bằng `get_children()` |
| [Clang – class `CFG` (Doxygen)](https://clang.llvm.org/doxygen/classclang_1_1CFG.html) | CFG của Clang – dùng cho Phase 4 (dựng CFG, test path) |
