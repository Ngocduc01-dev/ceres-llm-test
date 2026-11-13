# Phase 0 – Hướng dẫn: Chuẩn bị môi trường, build và parse

> Mục tiêu: một người bất kỳ trong nhóm, trên máy bất kỳ, chạy 3 lệnh là có
> (1) Ceres build xong có đo độ phủ, (2) số liệu độ phủ baseline,
> (3) bằng chứng libclang parse được toàn bộ source.

---

## 1. Tổng quan

```
Dockerfile ──► image ceres-testgen:phase0
                     │
   build.sh  ────────┤  CMake + Ninja + GCC 14 (--coverage)  ──► thư viện ceres + 175 test có sẵn
                     │                                         ──► compile_commands.json
   coverage.sh ──────┤  ctest + gcovr                          ──► độ phủ baseline (C1, C2)
                     │
   parse_check.py ───┘  libclang + compile_commands.json       ──► danh sách unit, file parse lỗi
```

Code gốc của Ceres nằm trong submodule `ceres-solver/` (không sửa gì bên trong). Code của nhóm nằm ở gốc repo:

```
ceres-llm-test/
├── ceres-solver/                # submodule, chốt tag 2.2.0
├── docker/Dockerfile
├── scripts/
│   ├── run_docker.sh            # chạy 1 lệnh bên trong container
│   ├── build.sh                 # build Ceres có đo độ phủ
│   ├── coverage.sh              # chạy test có sẵn + đo độ phủ baseline
│   └── parse_check.py           # parse thử bằng libclang
├── data/compile_commands.json   # sinh ra sau build (không commit)
├── reports/baseline/            # độ phủ baseline (2.2.0) + index.html
├── reports/parse/               # kết quả parse
├── reports/archive/             # kết quả các lần đo trước, giữ để so sánh
├── docs/                        # PLAN.md, file này, phân tích so sánh baseline
└── logs/                        # phase0-log.md + raw/ (log thô từng lệnh)
```

---

## 2. Các bước chạy

Yêu cầu trên máy: **Docker Desktop** (đang chạy) và **Git Bash**. Không cần cài compiler, CMake hay Python.

```bash
# 0. Clone kèm submodule ceres-solver (đã chốt tag 2.2.0)
git clone --recursive https://github.com/Ngocduc01-dev/ceres-llm-test.git
cd ceres-llm-test
git submodule status               # kiểm tra: ceres-solver phải là (2.2.0)

# 1. Build image (1 lần, ~1–5 phút)
docker build -t ceres-testgen:phase0 docker

# 2. Build Ceres có coverage (~15 phút lần đầu, các lần sau nhanh nhờ ccache)
#    JOBS = số file compile song song. Docker 8 GB RAM thì để 4, nhiều RAM hơn thì tăng.
scripts/run_docker.sh env JOBS=4 bash scripts/build.sh

# 3. Chạy 175 test có sẵn + đo độ phủ baseline (~1–1.5 tiếng; JOBS = số test chạy song song)
scripts/run_docker.sh env JOBS=14 bash scripts/coverage.sh
#    Chỉ xuất lại báo cáo, không chạy lại test (~2 phút):
scripts/run_docker.sh env SKIP_TESTS=1 bash scripts/coverage.sh

# 4. Parse thử toàn bộ source bằng libclang (~8 phút)
scripts/run_docker.sh env JOBS=6 python3 scripts/parse_check.py
```

Không có Docker (chạy thẳng trên Linux/WSL Ubuntu 24.04): cài gói như trong Dockerfile rồi chạy `bash scripts/build.sh` … như trên, bỏ phần `run_docker.sh`. Build sẽ nằm ở `~/ceres-build-cov`.

Xem kết quả:
- `reports/baseline/print_summary.txt`: % dòng, % nhánh
- `reports/baseline/html/index.html`: mở bằng trình duyệt để xem từng file, dòng nào/nhánh nào chưa phủ
- `reports/parse/summary.txt`: số file parse được, số unit

---

## 3. Vì sao làm như vậy

### 3.1. Vì sao dùng Docker?
- **Cả nhóm cùng một môi trường.** 5 người, 5 máy (Windows, Mac, Linux, version compiler khác nhau). Không có Docker thì sẽ có kiểu "máy tao chạy được, máy mày lỗi". Docker đóng gói đúng version GCC, CMake, Eigen, Clang vào một image, ai chạy cũng ra cùng kết quả.
- **Ceres là code Linux/C++.** Trên Windows phải dùng MSVC hoặc MinGW, cờ đo độ phủ và gcov hoạt động khác, rất dễ lỗi. Container Ubuntu giúp tránh hết.
- **Kết quả lặp lại được.** Khi báo cáo, số liệu độ phủ phải chạy lại ra đúng số đó. Môi trường cố định là điều kiện cần.
- **Không làm bẩn máy.** Cài/xoá thoải mái, xoá container là sạch.

### 3.2. Vì sao Ubuntu 24.04 + GCC 14?
- Ubuntu 24.04 có sẵn trong apt: GCC 14, CMake 3.28 (Ceres 2.2.0 cần ≥ 3.16), Eigen 3.4 (cần ≥ 3.3), glog 0.6, gflags 2.2, Clang 18. Không phải tự build cái gì.
- **GCC vì đo độ phủ bằng gcov.** gcov là công cụ đo độ phủ đi kèm GCC, đếm được cả dòng (C1) lẫn nhánh (C2).
- **GCC 14 cụ thể** vì có thêm cờ `-fcondition-coverage` (đo điều kiện con, C3). Hiện tại chỉ làm C2, nhưng nếu thầy hỏi C3 thì không phải đổi môi trường.

### 3.3. Vì sao CMake (và Ninja)?
- **CMake là hệ thống build chính thức của Ceres** (`CMakeLists.txt` ở gốc repo). Không tự viết Makefile, dùng đúng cách project gốc build thì ít lỗi nhất.
- CMake cho bật/tắt tính năng bằng option `-D<TÊN>=OFF`, nên tắt được các phần không cần.
- **Cẩn thận:** gõ sai tên option, CMake **không báo lỗi**, chỉ in cảnh báo "Manually-specified variables were not used" rồi build với giá trị mặc định. Tên option khác nhau giữa các phiên bản Ceres (2.2.0: `SUITESPARSE`, `LAPACK`…; bản mới hơn: `WITH_SUITESPARSE`…). Sau khi build phải xem log có dòng cảnh báo đó không.
- CMake sinh được **`compile_commands.json`** (option `CMAKE_EXPORT_COMPILE_COMMANDS=ON`): file ghi lại chính xác lệnh compile của từng file `.cc` (include path, macro, chuẩn C++17). libclang cần file này mới parse đúng (xem 3.6).
- **Ninja** thay cho `make`: build song song nhanh hơn, CMake hỗ trợ sẵn.
- **ccache**: lưu kết quả compile, lần build sau chỉ compile lại file đã đổi. Phase 6 compile lại rất nhiều lần nên cái này tiết kiệm nhiều thời gian.

### 3.4. Vì sao build với những option này?

| Option | Giá trị | Lý do |
|---|---|---|
| `CMAKE_BUILD_TYPE` | `Debug` | Không tối ưu hoá, để số liệu độ phủ khớp với source |
| `CMAKE_CXX_FLAGS` | `--coverage -O0` | `--coverage` bảo GCC chèn bộ đếm vào mỗi dòng/nhánh. `-O0` để compiler không gộp hay xoá nhánh (nếu tối ưu, nhánh trong source và nhánh gcov đếm sẽ lệch nhau) |
| `BUILD_TESTING` | `ON` | Cần 175 test có sẵn của Ceres để đo baseline, và để làm test mẫu cho LLM |
| `BUILD_EXAMPLES`, `BUILD_BENCHMARKS`, `BUILD_DOCUMENTATION` | `OFF` | Không thuộc phạm vi unit test, chỉ làm build lâu hơn |
| `MINIGLOG=OFF`, `GFLAGS=ON` | | Dùng glog/gflags thật (cài từ apt). Phase 6 cần hook hàm xử lý lỗi của glog (`google::InstallFailureFunction`) để gọi `__gcov_dump()` trước khi `CHECK` làm chương trình dừng |
| `USE_CUDA` | `OFF` | Không có GPU trong container. Code CUDA bị loại khỏi phạm vi |
| `SUITESPARSE`, `LAPACK`, `EIGENMETIS` | `OFF` | Thư viện ngoài tuỳ chọn. Tắt để ít dependency, build ổn định. Code liên quan sẽ không được compile, cần ghi rõ trong báo cáo là ngoài phạm vi |
| `EIGENSPARSE` | `ON` | Giữ 1 bộ giải sparse (bằng Eigen, không cần thư viện ngoài) để các phần sparse của Ceres vẫn được compile và test |
| `SCHUR_SPECIALIZATIONS` | `OFF` | Tắt các bản sinh tự động trong `internal/ceres/generated/` (hàng chục bản template gần giống nhau cho từng kích thước ma trận). Build nhanh hơn, số liệu không bị phình bởi code sinh tự động. Bản đo lần 1 của nhóm để `ON`, xem `docs/baseline-comparison.md` |
| `CMAKE_C/CXX_FLAGS` có `-fprofile-update=atomic` | | Bộ đếm độ phủ tăng kiểu atomic, an toàn khi test chạy đa luồng (không thì gcov ra số âm) |
| `CMAKE_EXPORT_COMPILE_COMMANDS` | `ON` | Sinh `compile_commands.json` cho libclang |

### 3.5. Vì sao gcovr?
- gcov chỉ cho kết quả từng file một, dạng text khó đọc. **gcovr** gom toàn bộ thành một báo cáo: tổng %, từng file, xuất được JSON (cho script Phase 4/6 đọc) và HTML (cho người xem).
- Có sẵn bộ lọc: chỉ tính code Ceres, bỏ file test, bỏ googletest/gmock (Ceres 2.2.0 để sẵn trong `internal/ceres/gmock_gtest_all.cc`, `gmock/`, `gtest/`), bỏ file hỗ trợ test (`*test_util*`).
- Xuất thêm `reports/baseline/index.html`: trang tổng quan 1 file (commit vào repo được). Bản chi tiết từng dòng `reports/baseline/html/` (~20 MB) không commit, sinh lại bằng `SKIP_TESTS=1`.
- `--exclude-throw-branches`: GCC sinh thêm nhánh ẩn cho mỗi chỗ có thể ném exception. Đó không phải nhánh trong source, tính vào sẽ làm % nhánh thấp vô lý.
- `--exclude-unreachable-branches`: bỏ nhánh compiler sinh ra mà không bao giờ đi tới được.

### 3.6. Vì sao libclang (mà không phải tree-sitter, regex...)?
- **libclang là chính front-end của compiler Clang**, nên nó hiểu C++ đầy đủ: template, namespace, overload, macro, kiểu dữ liệu. Ceres dùng template và Eigen rất nhiều, parser "đoán" như tree-sitter hay regex sẽ sai.
- Biết **lời gọi hàm trỏ tới hàm nào thật sự** (`cursor.referenced`) → cần cho code graph (Phase 1).
- Biết **kiểu của tham số** → cần cho bước sinh input (Phase 4).
- Có **binding Python** (`clang.cindex`), viết script nhanh, không phải viết C++.
- Đọc được `compile_commands.json` trực tiếp → parse đúng cờ như lúc compile thật.

### 3.7. Vì sao vẫn compile bằng GCC mà parse bằng Clang?
- Đo độ phủ dùng gcov → phải compile bằng GCC.
- Phân tích AST dùng libclang → tốt nhất cho C++.
- Hai việc độc lập, cùng đọc một source, cùng một bộ cờ (từ `compile_commands.json`). Script parse bỏ đi các cờ chỉ GCC hiểu (`--coverage`).

### 3.8. Vì sao build nằm trong Docker volume chứ không trên ổ E:?
- Repo trên ổ Windows được "mount" vào container. Ghi hàng nghìn file nhỏ (`.o`, `.gcno`, `.gcda`) qua mount này **rất chậm**.
- Nên thư mục build để trong Docker volume `ceres-testgen-build` (nằm trong Linux). Source vẫn đọc từ ổ E:, báo cáo vẫn ghi ra `reports/`.

### 3.9. Vì sao không quan tâm test FAIL khi đo baseline?
- Đề bài: không quan tâm PASS/FAIL, chỉ đo độ phủ. Test FAIL vẫn chạy qua code, vẫn tính phủ.
- `coverage.sh` vẫn chạy tiếp khi `ctest` báo lỗi, và lưu log để biết test nào FAIL.

---

## 4. Lưu ý quan trọng phát hiện khi làm

- **Nhóm chốt Ceres release 2.2.0** (tag `2.2.0`) để số liệu cố định, không bị commit mới của Ceres làm thay đổi. Lần làm đầu tiên đo trên `e831bfef` (bản phát triển sau 2.2.0), kết quả giữ trong `reports/archive/baseline-e831bfef/`.
- Ceres 2.2.0 dùng **glog**. `CHECK` sai gọi `abort()` → gcov mất dữ liệu của lần chạy đó. Phase 6 xử lý bằng `google::InstallFailureFunction` (gọi `__gcov_dump()` trước khi thoát) + signal handler cho `SIGSEGV`/`SIGTERM`.
- Ceres 2.2.0 để sẵn googletest trong `internal/ceres/` → phải loại khỏi đo độ phủ và khỏi code graph, nếu không số liệu bị phình (xem `docs/baseline-comparison.md`).
- Bộ test của 2.2.0 ăn RAM hơn: build `JOBS=8` trên Docker 8 GB bị lỗi `Cannot allocate memory` → dùng `JOBS=4` (ninja build tiếp từ chỗ dừng, không phải build lại từ đầu).

---

## 5. Lỗi hay gặp và cách xử lý

| Lỗi | Nguyên nhân | Cách xử lý |
|---|---|---|
| Thư mục `ceres-solver/` trống | Chưa tải submodule | `git submodule update --init` |
| `error: ... Cannot allocate memory` khi compile | Hết RAM khi compile nhiều file cùng lúc | Giảm `JOBS` (4 với Docker 8 GB) rồi chạy lại `build.sh` |
| Docker Desktop không lên, log có `sailor-ingest.sock: rename` | File socket cũ bị hỏng | Khởi động lại Windows |
| `$'\r': command not found` | Script bị đổi xuống dòng sang CRLF | `.gitattributes` đã ép LF; nếu vẫn lỗi: `git add --renormalize .` |
| Compiler bị kill giữa chừng (`Killed`, `signal 9`) | Hết RAM | Giảm `JOBS` |
| gcovr: `Got negative hit value` | Test đa luồng ghi đè bộ đếm | Đã thêm `-fprofile-update=atomic` vào build; gcovr đã đặt chế độ cảnh báo |
| libclang: `Unknown template argument kind 280` | Binding Python thiếu tên cho loại node mới | Script đã so sánh bằng `_kind_id` |
| ctest báo `(Timeout)` cho test `ba_*` | Test bundle adjustment ở Debug + atomic chạy 15–20 phút | `TEST_TIMEOUT` mặc định 3600s; chạy lại riêng test lỗi: `env RERUN_FAILED=1 bash scripts/coverage.sh` (giữ dữ liệu cũ) |

## 6. Kết quả chính thức (Ceres 2.2.0)

| Chỉ số | Giá trị |
|---|---|
| Test có sẵn | 175/175 PASS |
| Phủ dòng (C1) | 85.8% (11886/13846) |
| **Phủ nhánh (C2)** | **59.5% (8770/14745)** |
| Parse libclang | 292/292 file không lỗi |
| Số unit | 1540 |

Khớp với lần đo đầu của nhóm khi dùng cùng bộ lọc (48.3% vs 47.9%) – xem `docs/baseline-comparison.md`.
Chi tiết từng bước, vấn đề gặp phải: `logs/phase0-log.md`.

## 7. Tiêu chí hoàn thành Phase 0

- [x] `docker build` thành công
- [x] `build.sh` thành công, có `data/compile_commands.json`
- [x] `coverage.sh` ra được % dòng và % nhánh baseline
- [x] `parse_check.py` chạy hết, ghi lại số file parse lỗi (nếu có) và số unit
- [x] Ghi log vào `logs/phase0-log.md`
- [x] Build với `-fprofile-update=atomic` (không còn lỗi bộ đếm âm)
- [x] So khớp với lần đo đầu của nhóm
