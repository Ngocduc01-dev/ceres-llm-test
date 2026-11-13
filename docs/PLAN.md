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

---

## 2. Tổng quan pipeline

```
Phase 0  Build + parse
   │
Phase 1  Code graph ──► Phase 2  Liệt kê & phân loại unit
                              │
              ┌───────────────┘
              ▼
Phase 3  Gom context ─► Phase 4  Lập kế hoạch nhánh ─► Phase 5  Sinh test
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

**Đầu ra:** `context/<id>.txt`, `build_context.py`.

---

### Phase 4 – Lập kế hoạch test theo C2
**Phụ trách:** C

**Mục tiêu:** biết unit có những nhánh nào và input nào đi vào từng nhánh.

**Các bước:**
1. **Lấy danh sách nhánh mục tiêu từ gcov** (`gcovr --json`, lọc theo dòng của unit), không tự dựng CFG để đo – vì độ phủ cuối cùng do gcov đo.
2. Dùng AST **gắn mỗi nhánh gcov với điều kiện trong source**, vd. "dòng 134: `if (num_rows == 0)` – cần True và False" → đưa vào prompt.
3. Vòng lặp: 0 lần, 1 lần, nhiều lần.
4. Cho LLM viết **kế hoạch ngắn** trước khi viết code: mỗi nhánh cần input dạng gì.
5. **Bộ sinh ngẫu nhiên** (seed cố định) theo kiểu tham số:
   - `double`: 0, âm, dương, rất nhỏ, rất lớn, NaN, Inf, ngẫu nhiên
   - `int`: 0, 1, -1, ngẫu nhiên trong khoảng hợp lý
   - Eigen: kích thước ngẫu nhiên 0–5, giá trị ngẫu nhiên
   - con trỏ: `nullptr` và con trỏ hợp lệ

   Random chạy trước để phủ nhánh dễ; LLM xử lý nhánh random không vào được.

**Đầu ra:** `plan/<id>.json` (nhánh, điều kiện, input gợi ý), `random_gen.py`.

---

### Phase 5 – Sinh code test
**Phụ trách:** D

**Mục tiêu:** mỗi unit có một file GoogleTest.

**Quy ước:**
- Mỗi unit một file `gen_tests/<id>_test.cc`.
- Tên test: `TEST(Gen_u0421, Branch_134_True)`.
- **Không assert theo EO** – chỉ gọi hàm, có thể in kết quả thực tế.
- Seed cố định.

**Cách gọi unit khó:**

| Tình huống | Cách xử lý |
|---|---|
| `static` / anonymous namespace | `#include "foo.cc"` thẳng vào file test |
| Method `private` | Gọi qua method public, hoặc `#define private public` trước include (hack – ghi rõ trong báo cáo) |
| Template | Instantiate với kiểu đã chọn ở Phase 2 |
| Dependency nặng | Class con giả lập / stub (vd. `CostFunction` đơn giản) |

**Prompt gồm:** context (P3) + kế hoạch (P4) + quy ước file test + 1 test mẫu hoàn chỉnh + yêu cầu chỉ trả về 1 code block.

**Đầu ra:** `generate.py` (vào: id unit → ra: file `.cc`).

---

### Phase 6 – Compile, chạy và vòng lặp phủ nhánh
**Phụ trách:** D (compile + sửa), A (đo phủ)

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

| Người | Phase | Tuần 1 | Tuần 2 | Tuần 3+ |
|---|---|---|---|---|
| A | 0 (build), 6 (đo phủ) | Docker, build, baseline | Script đo phủ theo unit, hook `__gcov_dump` | Hỗ trợ sửa lỗi build/đo |
| B | 0 (parse), 1, 2 | Parse, code graph | `units.json`, phân loại, thứ tự | Sửa unit parse lỗi |
| C | 3, 4 | Thử prompt tay trên ~10 unit dễ | `build_context.py`, kế hoạch nhánh, bộ sinh random | Tinh chỉnh context cho unit khó |
| D | 5, 6 (compile/sửa) | Quy ước file test, CMake target | `generate.py`, vòng sửa lỗi + vòng phủ | Tăng tỉ lệ compile được |
| E | 7, 8 | Helper tạo input Ceres (`Problem`, ma trận) | `run_all.py`, cache, log | Chạy toàn bộ, hậu xử lý, báo cáo |

**Chốt ngay buổi đầu:**
1. Format `units.json` (B → C, D).
2. Format `results/<id>.json` (D → E).
3. Phạm vi unit: thư mục nào trong phạm vi, cái gì bị loại.
4. Model LLM, API key dùng chung, trần chi phí.

**Mốc hết tuần 2:** chạy trọn P3 → P6 trên ~20 unit. Chưa được thì dồn người vào chỗ kẹt trước khi chạy toàn bộ.

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
