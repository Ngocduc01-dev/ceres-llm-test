# Phase 6 – log

## Bước 1 – Script compile / chạy / đo phủ (2026-11-15)

- Viết `scripts/phase6.py` và `scripts/phase6_main.cc` (cách làm xem `docs/phase6-guide.md`).
- **Thử trên u0540:** compile, chạy và đo được. C2 gcov 9/10, trong khi CFG 4/4 – gcov tách `a && !b` thành 6 nhánh.
- **Thử 20 unit smoke test, lần 1** – thấy 2 lỗi đo:
  - **u0436** (destructor template): gcov gắn nhánh của `if` vào dòng `}`, và `--exclude-unreachable-branches` bỏ mất nhánh đó → bỏ cờ này.
  - **u0485:** lệnh `CHECK(...) << "..."` viết trên 2 dòng, nên pattern theo từng dòng không loại được nhánh ở dòng thứ hai → tự tính các dòng thuộc lệnh `CHECK` (đến dấu `;`) rồi bỏ nhánh trên các dòng đó.
- Kiểm tra hook `__gcov_dump`: u0467 bị `CHECK` sai (`options.context != nullptr`) nhưng vẫn ghi được 55 file `.gcda` → hook chạy đúng.

## Bước 2 – Smoke test 20 unit (`reports/phase6/smoke/`)

| | |
|---|---|
| Compile được | 19/20 (u0536: dùng `kImpossibleValue` không có namespace) |
| Test case | 58 pass, 2 `check_fail` (u0467: thiếu `context` khi tạo `LinearSolver`) |
| C1 | 144/154 = 94% |
| C2 gcov | 88/91 = 97% |
| Phủ đủ 100% nhánh | 13 unit |

Nhánh còn thiếu:
- u0540, u0539: thiếu một tổ hợp điều kiện con của `&&` / `||`; theo CFG thì đã đủ nhánh.
- u0553: thiếu thật – nhánh `Plus()` của manifold trả về `false`.

## Bước 3 – 250 unit đầu theo `topo_level` (`reports/phase6/batch1/`)

**Sinh test:**
- `node scripts/generate.mjs --limit 250 --jobs 3`, thêm tùy chọn `--jobs` cho chạy song song.
- 250/250 thành công, khoảng 25 phút, mỗi lần gọi khoảng 4,3–4,7k token đầu vào.
- Cả 250 unit đều ở `topo_level` 0, phần lớn là getter, destructor, hàm 1–3 dòng.

**Kết quả:**

| | |
|---|---|
| Compile được | 234/250 (94%) |
| Test case | 236 pass, 0 fail, 0 crash, 0 timeout |
| C1 | 504/507 = 99% |
| C2 gcov | 243/243 = 100% (80 unit có nhánh; 154 unit không có nhánh nào theo gcov) |

**16 unit không compile được, theo nguyên nhân:**

| Nguyên nhân | Unit | Loại lỗi |
|---|---|---|
| `#define private public` làm hỏng header chuẩn (`<sstream>`, `<any>`: "redeclared with different access") | u0054, u0055 | **lỗi prompt** |
| C API (`c_api.cc`): context thiếu `ceres/c_api.h`; class nằm trong namespace không tên của `.cc` | u0243–u0246 | **lỗi context (Phase 3)** |
| Functor tự viết thiếu hàm `Plus` / `Minus` mà `AutoDiffManifold` cần | u0004–u0006 | lỗi test |
| Gọi sai constructor hoặc kiểu (`SubsetManifold(int, vector<bool>)`, kiểu `map` của `OrderedGroups`, overload `VariadicEvaluateImpl`, thiếu `SphereManifold`) | u0065, u0197, u0198, u0200–u0202 | lỗi test |
| `NumTraits<double>::max_digits10` không có trong Eigen 3.4.0 của image | u0163 | môi trường – unit không compile được với Eigen hiện tại |

**Đề xuất sửa (chưa làm):**
- Thay `#define private public` bằng cờ `-fno-access-control` của g++ khi compile test. Cách này không cần sửa code test và không làm hỏng header chuẩn. Sau đó bỏ quy tắc đó khỏi prompt.
- Phase 3: context của `c_api.cc` thêm `#include "ceres/c_api.h"`; các hàm trong namespace không tên cần `#include` file `.cc`.

## Bước 4 – Đổi C2 sang đếm theo điểm rẽ nhánh, đo lại 270 unit

**Vì sao đổi:** số nhánh gcov thường (mức mã máy) không cùng hệ quy chiếu với CFG.
- u0540: gcov đếm 10 nhánh, CFG 4.
- u0553: gcov đếm 20 nhánh, CFG 12.

**Đổi thành:** `gcovr --decisions`, đếm 2 nhánh cho mỗi `if`/`for`/`while`, kể cả khi điều kiện là `a && b`.
- Chỉ giữ một loại nhánh này, bỏ hẳn số nhánh gcov thường.
- Thử trên 6 unit smoke: mẫu số khớp số nhánh CFG ở cả 6.

**Hai chỗ gcovr bỏ sót, script tự suy ra:**
- u0436: `if` có nhánh bị gắn sang dòng `}`.
- u0482: toán tử `?:`.

**Trang tổng quan mới:**
- `reports/phase6/gen_coverage.html`, cùng kiểu với `reports/baseline/index.html`.
- Bản chi tiết từng file ở `reports/phase6/html/`, không commit.
- Cột Branches là số nhánh theo điểm rẽ nhánh.

**Kết quả 270 unit (20 smoke + 250 đầu):**

| | |
|---|---|
| Compile được | 253/270 |
| Test case | 294 pass, 2 `check_fail` |
| C1 | 648/661 = 98% |
| C2 | 59/60 = 98% (16 unit có nhánh, 15 unit phủ đủ) |
| Nhánh còn thiếu | u0553 dòng 229: `Plus()` trả về `false` |

**Số nhánh đo được lệch số nhánh CFG ở 4 unit – lỗi CFG Phase 4, không phải lỗi đo:**

| Unit | Lỗi CFG |
|---|---|
| u0025, u0059 (`Apply` rỗng, nhiều bản đặc tả) | lấy nhầm CFG của bản `Apply` khác (cùng tên, cùng số tham số) |
| u0205 (`RotationMatrixToQuaternion(const T*, T*)`) | lấy nhầm CFG của overload `(const MatrixAdapter&, T*)` – cùng số tham số, khác kiểu |
| u0470 (`TolerantLoss::Evaluate`) | Clang tạo khối `static init` cho biến `static constexpr` → bị đếm thành 1 điểm rẽ nhánh (4 unit có `static init` trong CFG) |

Hướng sửa (chưa làm):
- `build_cfg.py` so khớp overload thêm theo **kiểu** tham số, không chỉ số lượng.
- Không coi khối `static init` là điểm rẽ nhánh.
