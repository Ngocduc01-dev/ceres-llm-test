# Nhật ký Phase 0

Ghi theo thứ tự thời gian: làm gì, kết quả ra sao, gặp vấn đề gì, xử lý thế nào, vì sao.

> **Tóm tắt:** Phase 0 được làm 2 lần.
> - **Phần A (Bước 1–10):** làm thử trên bản phát triển `e831bfef` của Ceres – dựng Docker, script, xử lý các lỗi môi trường.
> - **Phần B (Bước 11–17): làm lại trên Ceres release 2.2.0** – nhóm chốt bản này để số liệu cố định. **Đây là kết quả chính thức.** So khớp với lần đo đầu của nhóm: `docs/baseline-comparison.md`.
>
> **Kết quả chính thức (2.2.0):** 175/175 test PASS · C1 = 85.8% · **C2 = 59.5%** (8770/14745 nhánh) · parse 292/292 file · 1540 unit.

---

# Phần A – Làm thử trên `e831bfef`

## Bước 1 – Lấy source Ceres

**Làm gì:** clone `https://github.com/ceres-solver/ceres-solver` về `E:\Code\ceres-solver`.

**Kết quả:**
- Commit: `e831bfef` (bản phát triển sau tag `2.2.0`, `git describe` = `2.2.0-286-ge831bfef`). (Sau đó nhóm chốt dùng release 2.2.0 – xem Phần B.)
- Đếm sơ bộ: 551 file `.cc`/`.h` trong `internal/` và `include/`, tổng ~106k dòng → đúng quy mô ~100k LOC của đề.
- 44 file trong `internal/ceres/generated/` (code sinh tự động, sẽ loại khỏi phạm vi).

**Vấn đề:** thư mục `third_party/abseil-cpp` và `third_party/googletest` trống.
**Nguyên nhân:** đây là git submodule, `git clone` thường không tải về.
**Xử lý:** `git submodule update --init --recursive`. Abseil (`lts_2025_01_27`) và googletest (`v1.16.x`) đã tải xong.

Ban đầu làm trong một bản clone riêng của Ceres; sau đó chuyển toàn bộ sang repo nhóm `ceres-llm-test` (Ceres là submodule `ceres-solver/`, cùng commit `e831bfef`) – xem Bước 10.

---

## Bước 2 – Đọc CMakeLists.txt để biết cần gì

**Làm gì:** đọc `CMakeLists.txt` trước khi viết script build.

**Phát hiện:**
1. **Ceres bản mới dùng Abseil thay cho glog** (`find_package(absl ...)`, dùng `third_party/abseil-cpp` nếu có). → Không cần cài glog/gflags. Nhưng kế hoạch Phase 6 (hook glog để gọi `__gcov_dump`) phải đổi: dùng signal handler cho `SIGABRT` thay thế.
2. Tên option thật có tiền tố `WITH_`: `WITH_SUITESPARSE`, `WITH_LAPACK`, `WITH_CUDA`, `WITH_EIGENMETIS`, `WITH_SCHUR_SPECIALIZATIONS`. PLAN.md ghi `-DSUITESPARSE=OFF` là sai → đã sửa trong script.
3. Yêu cầu: CMake ≥ 3.22, C++17, Eigen 3.3.4–5. Bắt buộc chỉ có Eigen + Threads, còn lại đều tuỳ chọn.
4. Có **105 test có sẵn** đăng ký bằng `ceres_test(...)` trong `internal/ceres/CMakeLists.txt`.

---

## Bước 3 – Kiểm tra máy

| Thứ | Có không | Ghi chú |
|---|---|---|
| Docker | Có (29.8.0) nhưng đang tắt | Bật Docker Desktop |
| WSL Ubuntu | Có, đang chạy | Không dùng trực tiếp, để mọi người dùng chung Docker |
| gcc / g++ / clang / cmake trên Windows | Không | Không cần, đã có trong Docker |
| CPU | 16 luồng | Build song song `-j16` |

**Quyết định:** làm tất cả trong Docker (lý do: xem `docs/phase0-guide.md` mục 3.1).

---

## Bước 4 – Viết Dockerfile và script

Đã tạo (lý do từng lựa chọn: `docs/phase0-guide.md` mục 3):
- `docker/Dockerfile`: Ubuntu 24.04, GCC 14, CMake, Ninja, ccache, Eigen, gcovr, lcov, Clang 18 + libclang Python.
- `scripts/run_docker.sh`: chạy lệnh trong container.
- `scripts/build.sh`: build có `--coverage -O0`, xuất `compile_commands.json`.
- `scripts/coverage.sh`: chạy `ctest` + `gcovr`.
- `scripts/parse_check.py`: parse thử bằng libclang, đếm unit.
- `.gitattributes`: ép file `.sh`/`.py` xuống dòng kiểu LF.

**Hai vấn đề đã lường trước và xử lý luôn:**
1. **Windows lưu file kiểu CRLF**, bash trong Linux đọc sẽ lỗi `$'\r': command not found`. → `.gitattributes` ép LF.
2. **Ghi build qua ổ Windows mount vào container rất chậm.** → Thư mục build đặt trong Docker volume `ceres-testgen-build`.
3. **Git Bash tự đổi đường dẫn** `/work/...` thành `C:/Program Files/Git/work/...` khi gọi `docker`. → `export MSYS_NO_PATHCONV=1` trong `run_docker.sh`.

**Sửa PLAN.md** cho khớp thực tế: tên option `WITH_...`, bỏ glog, hook `SIGABRT` thay cho hook glog.

---

## Bước 5 – Khởi động Docker: GẶP LỖI

**Làm gì:** bật Docker Desktop để build image.

**Vấn đề:** chờ >10 phút, `docker info` vẫn báo không kết nối được daemon.

**Tìm nguyên nhân:** đọc log `AppData\Local\Docker\log\host\com.docker.backend.exe.log`:
```
backend crashed ... initializing Ingest server: listening on unix://.../Docker/run/sailor-ingest.sock: rename ...
```
→ Docker Desktop không tạo được file socket vì còn **file socket cũ bị hỏng** (`sailor-ingest.sock.stale`) từ lần chạy trước.

**Đã thử:**
1. Tắt hẳn Docker Desktop rồi mở lại → vẫn crash.
2. Xoá các file `*.stale` → Windows không xoá được (file socket hỏng, hiện `?????????` khi `ls`).

**Xử lý:** khởi động lại Windows để xoá các file socket hỏng. **Tạm dừng Phase 0 ở đây.**

**Phương án dự phòng (đã chuẩn bị sẵn):** WSL Ubuntu 24.04 trên máy cùng bản với Dockerfile, đã có gcc/cmake/python3, chỉ thiếu `ninja-build ccache gcovr lcov clang-18 libclang-18-dev python3-clang-18`. Các script đã được sửa để chạy được cả trong Docker lẫn trực tiếp trong WSL (tự nhận đường dẫn repo, build để ở `~/ceres-build-cov`).

---

**Kết quả:** sau khi khởi động lại Windows, Docker chạy bình thường (Docker 29.8.0, cấp cho container 16 CPU, 8 GB RAM).

---

## Bước 6 – Build Docker image

**Lệnh:** `docker build -t ceres-testgen:phase0 docker`
**Kết quả:** thành công, ~1 phút. Kiểm tra trong image:

| Công cụ | Version |
|---|---|
| gcc / gcov | 14.2.0 |
| cmake | 3.28.3 |
| gcovr | 7.0 |
| libclang (Python) | 18, import OK |

Log: `logs/raw/docker_build.log`

---

## Bước 7 – Build Ceres có đo độ phủ

**Lệnh:** `scripts/run_docker.sh env JOBS=8 bash scripts/build.sh`

**Vì sao `JOBS=8` chứ không phải 16:** container chỉ có 8 GB RAM. Compile C++ có template/Eigen ở chế độ Debug tốn ~0.5–1 GB mỗi file, chạy 16 file cùng lúc dễ hết RAM (compiler bị kill giữa chừng).

**Kết quả:** thành công, **15 phút 32 giây**, 759 bước compile/link (gồm cả abseil và googletest).

CMake báo tính năng:
- Bật: Eigen sparse solvers, Custom BLAS, Tests
- Tắt: SuiteSparse, CUDA, cuDSS, Accelerate, METIS, LAPACK, Schur specializations, Examples, Benchmarks, Documentation

→ Code của các tính năng bị tắt sẽ **không được compile**, nên ngoài phạm vi. Cần ghi rõ trong báo cáo cuối.

Có file `data/compile_commands.json` (424 KB) cho bước parse.

Log: `logs/raw/build.log`

---

## Bước 8 – Parse thử bằng libclang

**Lệnh:** `scripts/run_docker.sh env JOBS=6 python3 scripts/parse_check.py`

**Vấn đề 1:** script dừng ngay với lỗi `ValueError: Unknown template argument kind 280`.
- **Nguyên nhân:** libclang trả về một loại node mà binding Python không có tên. Cứ gọi `cursor.kind` là lỗi.
- **Xử lý:** so sánh bằng mã số (`cursor._kind_id`) thay vì tên, bỏ qua các node không cần.

**Vấn đề 2:** chạy được nhưng **rất chậm** (~15 giây/file, ước tính >1 tiếng cho 308 file).
- **Nguyên nhân:** duyệt **toàn bộ** cây AST, mà >90% cây là code của Eigen, abseil, thư viện chuẩn được `#include` vào, không phải code Ceres.
- **Xử lý:**
  1. **Cắt tỉa**: chỉ đi vào node nằm trong file của Ceres, không đi vào thân hàm (Phase 0 chỉ cần đếm unit).
  2. **Chạy song song** 6 process.
- **Kết quả:** 12 phút cho cả 308 file (đang chạy song song cùng lúc với test, nếu chạy riêng sẽ nhanh hơn).

**Kết quả:**

| Chỉ số | Giá trị |
|---|---|
| Số file `.cc` trong `internal/ceres` được compile | 308 (116 file thư viện + 192 file test có sẵn) |
| Parse không lỗi | **308/308** |
| Số unit (hàm/method có thân, trong phạm vi, không trùng) | **1503** |
| … nằm trong header `.h` | 712 (chủ yếu template, inline) |
| … theo loại | method 832, hàm template 225, hàm thường 190, constructor 182, destructor 74 |

→ **Kết luận: libclang đọc được toàn bộ code Ceres, Phase 1 (code graph) và Phase 2 (liệt kê unit) làm được.**

Chi tiết: `reports/parse/summary.txt`, `reports/parse/parse_report.json` (danh sách 1503 unit kèm file, dòng). Log: `logs/raw/parse.log`

---

## Bước 9 – Chạy test có sẵn và đo độ phủ baseline

**Lệnh:** `scripts/run_docker.sh env JOBS=8 bash scripts/coverage.sh`

**Chạy test:** **192/192 test PASS**, mất **28 phút**. Chậm nhất là các test bundle adjustment (`ba_*_threads_test`), mỗi cái 6–8 phút vì chạy ở chế độ Debug + có bộ đếm độ phủ. Log: `reports/baseline/ctest.log`

**Vấn đề 1:** gcovr báo `Could not create output file .../html/index.html`.
- **Nguyên nhân:** script quên tạo thư mục `html/`.
- **Xử lý:** thêm `mkdir -p`. Thêm option `SKIP_TESTS=1` để **chỉ xuất lại báo cáo** từ dữ liệu `.gcda` đã có, không phải chạy lại 28 phút test.

**Vấn đề 2:** gcovr báo `Got negative hit value ... 'branch 1 taken -111'`.
- **Nguyên nhân:** test đa luồng của Ceres (`*_threads_test`) cho nhiều luồng cùng tăng một bộ đếm độ phủ mà không khoá → bộ đếm bị ghi đè sai, ra số âm. Đây là lỗi đã biết của gcov (GCC bug 68080).
- **Xử lý:**
  - Lần này: cho gcovr cảnh báo thay vì dừng (`--gcov-ignore-parse-errors=negative_hits.warn_once_per_file`). Có 60 cảnh báo. Ảnh hưởng: vài nhánh có thể bị tính là "chưa phủ" dù đã chạy → baseline **có thể thấp hơn thực tế một chút**.
  - Lần build sau: đã thêm cờ `-fprofile-update=atomic` vào `build.sh` (bộ đếm tăng kiểu atomic, an toàn đa luồng). Cần build lại + chạy lại test (~45 phút) để có số chính xác.

**Vấn đề 3:** gcovr lỗi khi đọc file `CMakeFiles/3.28.3/CompilerIdCXX/...`.
- **Nguyên nhân:** đó là chương trình nháp CMake tự compile để dò compiler, cũng có cờ `--coverage`. Không phải code Ceres.
- **Xử lý:** loại thư mục đó (`--gcov-exclude-directories`).

**Kết quả độ phủ baseline (test có sẵn của Ceres):**

| Độ đo | Phủ / Tổng | % |
|---|---|---|
| **Dòng (C1 – câu lệnh)** | 12145 / 13975 | **86.9%** |
| **Nhánh (C2)** | 9536 / 14833 | **64.3%** |
| Hàm | 4099 / 4561 | 89.9% |

Phạm vi đo: 202 file trong `internal/ceres/` và `include/ceres/`, đã bỏ file test, code sinh tự động, abseil, googletest.

**File có độ phủ nhánh thấp nhất** (trong số file có ≥20 nhánh) – ứng viên tốt để test sinh ra cải thiện:

| File | Nhánh phủ | % |
|---|---|---|
| `internal/ceres/fake_bundle_adjustment_jacobian.cc` | 0/20 | 0% |
| `internal/ceres/linear_operator.cc` | 1/22 | 4.5% |
| `internal/ceres/cgnr_solver.cc` | 5/65 | 7.7% |
| `internal/ceres/event_logger.cc` | 3/21 | 14.3% |
| `internal/ceres/types.cc` | 34/210 | 16.2% |
| `internal/ceres/file.cc` | 8/32 | 25.0% |
| `include/ceres/product_manifold.h` | 157/540 | 29.1% |
| `internal/ceres/solver.cc` | 371/1031 | 36.0% |

**Nhận xét:**
- Test có sẵn đã phủ dòng rất cao (86.9%) nhưng **phủ nhánh chỉ 64.3%** → còn ~5300 nhánh chưa phủ. Đây là "đất" để test sinh tự động cải thiện, và cũng là lý do chọn C2 làm mục tiêu có ý nghĩa.
- Số "hàm" của gcov (4561) lớn hơn số unit của libclang (1503) vì gcov đếm **mỗi bản instantiate của template** và **mỗi bản inline trong từng file** là một hàm riêng. Báo cáo cuối dùng số unit của libclang (theo source), còn % phủ dùng số của gcov.

Báo cáo: `reports/baseline/print_summary.txt`, `summary.txt` (từng file), `summary.json`, `coverage.json` (chi tiết từng nhánh – Phase 4/6 sẽ đọc file này), `html/index.html` (mở bằng trình duyệt).

---

## Bước 10 – Chuyển sang repo nhóm và so sánh với kết quả cũ

**Làm gì:** đưa toàn bộ vào repo nhóm `ceres-llm-test`. Ở repo này Ceres là submodule `ceres-solver/`, cùng commit `e831bfef`.

**Sắp xếp lại:**
- Dockerfile, script đặt ở gốc repo (`docker/`, `scripts/`), không còn thư mục `testgen/`.
- Script tự tìm Ceres trong `ceres-solver/`. Trong Docker, Ceres được mount riêng vào `/work/ceres-solver` để đường dẫn luôn cố định, nhờ vậy dùng lại được bản build và ccache đã có.
- Thay Dockerfile và `build.sh`/`coverage.sh` cũ của nhóm. Bản cũ ghi cứng đường dẫn `/home/ngocduc/...` và dùng tên option của Ceres 2.2.0.
- Kết quả cũ (`report/baseline_coverage.json`, `logs/phase0_baseline.log`) được chuyển sang `reports/baseline-ceres-2.2.0/` để giữ lại so sánh.

**Kiểm tra:** chạy lại `coverage.sh` (chế độ `SKIP_TESTS=1`) và `parse_check.py` trong cấu trúc mới, so với kết quả trước khi chuyển. Log: `logs/raw/verify_coverage.log`, `logs/raw/verify_parse.log`.

**So sánh với kết quả cũ (C2 47.9% so với 64.3%):** nguyên nhân chính là kết quả cũ đo trên **Ceres 2.2.0**, không phải `e831bfef` như submodule đang trỏ. Kết quả cũ còn tính cả googletest (`gmock_gtest_all.cc`, gần 5000 nhánh) và code hỗ trợ test, và bật Schur specializations. Chi tiết: `docs/baseline-comparison.md`.

---

## Tổng kết Phần A (e831bfef)

| Tiêu chí | Trạng thái |
|---|---|
| Docker image build được | ✅ |
| Ceres build được có `--coverage` | ✅ 15.5 phút |
| Có `compile_commands.json` | ✅ |
| Đo được độ phủ baseline | ✅ C1 86.9%, C2 64.3% (192/192 test PASS) |
| libclang parse được toàn bộ | ✅ 308/308 file, 1503 unit |

**Tổng thời gian chạy máy:** ~1 tiếng (build 15', test 28', parse 12', báo cáo 2').

**Việc để lại / lưu ý cho phase sau:**
1. Build lại với `-fprofile-update=atomic` rồi đo lại baseline cho chính xác (60 cảnh báo bộ đếm âm ở lần này).
2. Phase 2 cần quyết định có tính các file hỗ trợ test (vd. `fake_bundle_adjustment_jacobian.cc`, `evaluator_test_utils.cc`) là unit hay không.
3. Test sinh ra ở Phase 6 nên **tránh chạy đa luồng** (hoặc dùng bản build atomic) để không gặp lại lỗi bộ đếm âm.
4. Chạy cả bộ test có sẵn mất 28 phút → ở Phase 6 **chỉ chạy test của từng unit**, không chạy lại toàn bộ.

---

# Phần B – Làm lại trên Ceres release 2.2.0 (chính thức)

## Bước 11 – Chuyển submodule về tag 2.2.0

**Vì sao:** nhóm chốt dùng **release 2.2.0** cho thống nhất và cố định. Bản phát triển (`master`) liên tục có commit mới, số liệu đo hôm nay và tuần sau sẽ khác nhau.

**Làm gì:** trong `ceres-solver/`: `git checkout 2.2.0`, xoá thư mục `third_party/abseil-cpp`, `third_party/googletest` còn sót lại từ `e831bfef` (2.2.0 không dùng 2 submodule này).

**Khác biệt của 2.2.0 so với `e831bfef`, phải sửa script theo:**

| | `e831bfef` | 2.2.0 | Đã sửa |
|---|---|---|---|
| Log / CHECK | Abseil (submodule) | **glog + gflags** | Dockerfile cài `libgoogle-glog-dev libgflags-dev` |
| Tên option CMake | `WITH_SUITESPARSE`, `WITH_LAPACK`, `WITH_CUDA`… | `SUITESPARSE`, `LAPACK`, `USE_CUDA`, `MINIGLOG`… | `build.sh` |
| googletest | submodule `third_party/googletest` | **để sẵn trong `internal/ceres/`** (`gmock_gtest_all.cc`, `gmock/`, `gtest/`) | `coverage.sh` loại thêm `.*/gtest/.*`; script parse/graph bỏ qua các file này |
| Số test | 192 | 175 | |

**Kiểm tra option:** log CMake **không có** dòng `Manually-specified variables were not used` → mọi option đều đúng tên. CMake tìm thấy glog 0.6.0, gflags 2.2.2.

## Bước 12 – Build

**Vấn đề:** build `JOBS=8` dừng giữa chừng: `error: .../gtest/gtest.h: Cannot allocate memory`.
- **Nguyên nhân:** hết RAM. Bộ test của 2.2.0 include `gtest.h` + `gmock.h` (rất nặng), 8 file compile cùng lúc vượt 8 GB của Docker.
- **Xử lý:** chạy lại `JOBS=4`. Ninja chỉ build tiếp phần chưa xong (138 bước còn lại), không build lại từ đầu.

**Kết quả:** BUILD OK. Tổng ~9 phút (6.5' lần 1 + 2.5' build tiếp), 472 bước.

## Bước 13 – Chạy test + đo độ phủ

**Vấn đề 1: rất chậm.** Với `-j6`, mỗi test bundle adjustment (`ba_*`, có 72 test) chạy ~14 phút → ước tính >2.5 tiếng.
- **Nguyên nhân:** cờ `-fprofile-update=atomic` (thêm ở Phần A để sửa lỗi bộ đếm âm) làm mỗi lần tăng bộ đếm thành 1 lệnh atomic → code tính toán nặng chậm đi nhiều.
- **Xử lý:** dừng, chạy lại với `-j14` (máy có 16 nhân).

**Vấn đề 2: 20 test bị timeout** (vượt 1200 giây, chậm nhất ~1180 giây khi chạy 14 test cùng lúc).
- **Vì sao quan trọng:** test bị timeout bị kill → gcov **không ghi** dữ liệu độ phủ của test đó.
- **Xử lý:** thêm vào `coverage.sh`:
  - `TEST_TIMEOUT` (mặc định 3600 giây).
  - `RERUN_FAILED=1`: chỉ chạy lại test fail/timeout lần trước (`ctest --rerun-failed`), **giữ dữ liệu `.gcda` cũ** để cộng dồn.
- **Kết quả chạy lại:** 20/20 PASS (35 phút), **độ phủ không đổi** (59.5%). 20 test này là biến thể (`user`/`threads`) của các test bundle adjustment đã chạy xong, đi qua cùng code.

**Kết quả:** **175/175 test PASS** (155 ở lần chạy chính + 20 chạy lại). **Không còn cảnh báo "bộ đếm âm"** (Phần A có 60) nhờ `-fprofile-update=atomic`.

| Độ đo | Phủ / Tổng | % |
|---|---|---|
| **Dòng (C1)** | 11886 / 13846 | **85.8%** |
| **Nhánh (C2)** | 8770 / 14745 | **59.5%** |
| Hàm | 5267 / 5881 | 89.6% |

205 file trong phạm vi. Trang tổng quan: `reports/baseline/index.html` (commit được, 140 KB). Bản chi tiết từng dòng: `reports/baseline/html/` (không commit).

## Bước 14 – Parse thử bằng libclang

`parse_check.py` (đã bỏ qua file googletest): **292/292 file không lỗi, 1540 unit** (method 871, function template 212, hàm tự do 205, constructor 177, destructor 75; 746 unit nằm trong header). ~8 phút.

Code graph Phase 1 đếm bằng cách khác cũng ra đúng **1540 unit** → hai cách đếm khớp nhau.

## Bước 15 – So khớp với lần đo đầu của nhóm (cũng 2.2.0)

Lần 1 của nhóm: C2 47.9%. Lần 2: C2 59.5%. Kiểm tra vì sao lệch:

1. Viết `scripts/compare_baseline.py` để so 2 báo cáo theo từng file.
2. **Chạy gcovr trên dữ liệu lần 2 nhưng dùng đúng bộ lọc của lần 1** → **C2 = 48.3%** (lần 1: 47.9%). → **Khớp**, chỉ lệch 0.4 điểm.
3. Phần lệch lớn (47.9 → 59.5) là do bộ lọc: lần 1 tính cả googletest (`gmock_gtest_all.cc` gần 5000 nhánh, phần lớn không phủ) và file hỗ trợ test.
4. Phần lệch nhỏ còn lại: lần 1 bật `SCHUR_SPECIALIZATIONS`, dùng GCC 13.

**Vấn đề nhỏ:** khi đo lại bằng bộ lọc lần 1, gcovr lỗi `UnknownLineType: %%%%%:10404-block 2` ở `gmock_gtest_all.cc` (output gcov của GCC 14 có dòng mà gcovr 7.0 chưa đọc được). Bộ lọc chính thức vốn loại file này nên không ảnh hưởng. Khi so sánh phải thêm `--gcov-ignore-parse-errors=all`.

Chi tiết: `docs/baseline-comparison.md`.

## Bước 16 – Trang HTML tổng quan

`coverage.sh` xuất thêm `reports/baseline/index.html`: 1 trang, có % dòng/nhánh/hàm và bảng từng file (đọc lại từ `coverage.json`, không gọi gcov lần nữa). Mở bằng trình duyệt là xem được.

## Bước 17 – Dọn dẹp, sắp xếp lại `reports/`

| Thư mục | Nội dung |
|---|---|
| `reports/baseline/` | **chính thức** (2.2.0, lần 2) |
| `reports/parse/` | parse libclang (2.2.0) |
| `reports/archive/baseline-2.2.0-lan1/` | lần đo đầu của nhóm (giữ để so sánh) |
| `reports/archive/baseline-e831bfef/`, `parse-e831bfef/` | Phần A (tham khảo) |

---

## Tổng kết Phase 0 (chính thức – Ceres 2.2.0)

| Tiêu chí | Trạng thái |
|---|---|
| Docker image (GCC 14, glog, Clang 18) | ✅ |
| Build Ceres 2.2.0 có `--coverage -fprofile-update=atomic` | ✅ ~9 phút (`JOBS=4`) |
| Có `compile_commands.json` | ✅ |
| Baseline | ✅ **175/175 PASS · C1 85.8% · C2 59.5%** |
| Khớp với lần đo đầu của nhóm | ✅ cùng bộ lọc: 48.3% vs 47.9% |
| libclang parse toàn bộ | ✅ 292/292 file, 1540 unit |

**Thời gian máy:** build ~9', test ~53' + chạy lại 35', parse ~8'.

**Lưu ý cho phase sau:**
1. Chạy cả bộ test có sẵn mất ~1.5 tiếng (vì atomic) → Phase 6 **chỉ chạy test của từng unit**.
2. Test sinh ra nên đặt timeout riêng và hook `__gcov_dump()` khi bị dừng (timeout / `CHECK` sai), nếu không sẽ mất dữ liệu độ phủ.
3. Còn **5975 nhánh chưa phủ** – mục tiêu của test sinh tự động.
