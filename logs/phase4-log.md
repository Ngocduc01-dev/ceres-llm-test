# Nhật ký Phase 4 – Dựng CFG cho từng unit bằng Clang

Mục tiêu: mỗi unit có `units/<id>/cfg.txt` – CFG do **tool** dựng (không để LLM tự dựng), gọn, có số dòng, để đưa vào prompt.
Script: `scripts/build_cfg.py`. Hướng dẫn chạy: `docs/phase4-guide.md`.

---

## Bước 1 – Thử Clang `debug.DumpCFG` trên 1 hàm

**Làm gì:** chạy `clang++-18 --analyze -Xclang -analyzer-checker=debug.DumpCFG` (cờ compile lấy từ `data/compile_commands.json`) cho `IsArrayValid` trong `array_utils.cc`.

**Vấn đề 1:** `-analyze-function=ceres::internal::InvalidateArray` không chạy hàm nào.
- **Nguyên nhân:** với C++, Clang cần cả danh sách kiểu tham số: `ceres::internal::InvalidateArray(const int64_t, double *)`.
- **Xử lý:** không lọc từng hàm nữa. Chạy **1 lần cho mỗi file `.cc`**, Clang in CFG của **mọi hàm** trong file; script tự tách theo tên. Nhanh hơn (292 lần chạy thay vì 1540) và không phải đoán đúng tên.

**Vấn đề 2:** mỗi file mất ~3 giây vì Clang còn chạy các checker phân tích đường đi mặc định.
- `-analyzer-disable-all-checks` → tắt luôn `DumpCFG` (không ra gì).
- **Xử lý:** `--analyzer-no-default-checks` – chỉ tắt checker mặc định, giữ `DumpCFG`.

**Vấn đề 3:** hàm trong header (746 unit) không có CFG.
- **Xử lý:** thêm `-analyzer-opt-analyze-headers`. Clang in cả hàm của Eigen, std (~3800 hàm/file) → script chỉ giữ hàm trong `internal/ceres/`, `include/ceres/`.

**Output thô rất nhiễu** (ví dụ 1 dòng `if (x != nullptr)` thành 5 bước `[B8.1] … [B8.5]` + `ImplicitCastExpr`), **không có số dòng**. Macro `CHECK` của glog bung ra hàng chục dòng in log.

## Bước 2 – Làm gọn output

`scripts/build_cfg.py` làm:

| Việc | Ví dụ |
|---|---|
| Thay tham chiếu `[Bx.n]` bằng biểu thức thật, bỏ `ImplicitCastExpr` | `T: if [B8.5]` → `T: if (x != nullptr)` |
| Chỉ giữ câu lệnh chính của khối (bỏ mẩu rời: hằng số, tên biến, `operator=`…) | `0; int i = 0;` → `int i = 0;` |
| Ghi rõ nhánh | `Succs (2): B7 B1` → `T→B7  F→B1` |
| Gom macro `CHECK` của glog thành 1 điểm quyết định, số dòng lấy từ `LogMessageFatal(file, dòng)` | `T: CHECK_LT(index, size_)   CHECK đúng→B6  CHECK sai→B8` |
| Gom macro `VLOG` (điều kiện ẩn theo mức log) | `T: VLOG – kiểm tra mức log của glog (nhánh log, không bắt buộc phủ)` |
| `break;` / `continue;` có 1 nhánh ra → **không** phải điểm quyết định | |
| Đánh dấu vế trái của `&&` / `||` (Clang tách thành nhiều khối) | `[vế trái của && / || – gộp với khối kế tiếp khi tính C2]` |
| Gắn số dòng `@L<số>`: so biểu thức với mã nguồn của unit; nhiều dòng khớp thì lấy dòng gần dòng vừa xác định | `B8 @L45` |

**Các lỗi gặp khi làm gọn và cách sửa:**
1. **CHECK_LT/CHECK_GT bị gắn ngược nhãn.** Glog viết `CHECK_op` bằng vòng `while`: nhánh True là *CHECK sai*. → Không dựa vào thứ tự T/F; nhánh "sai" = nhánh đi tới khối `LogMessageFatal`.
2. **`break;` bị đếm là điểm quyết định** (Clang coi `break` là terminator của khối) → chỉ tính khối có ≥ 2 nhánh ra. Ví dụ `DoglegStrategy::ComputeStep`: 16 → 11 điểm quyết định.
3. **Mất câu lệnh thật nằm chung khối với CHECK/VLOG** (vd. `search_direction *= approximate_eigenvalue_scale_;`) → chỉ bỏ phần của glog, giữ câu lệnh thật.
4. **Số dòng của `for`** không tìm được vì Clang in `for (...; i < size; ...)` → tìm dòng có `for(` và điều kiện.
5. **`++i` của vòng lặp thứ 2 bị gắn dòng vòng lặp thứ 1** → chọn dòng khớp gần dòng vừa xác định nhất.
6. **Số thực** `1.0` trong source, Clang in `1.` → chuẩn hoá trước khi so.
7. **`B1(Unreachable)`** trong danh sách nhánh làm script lỗi → đọc số khối bằng regex.

## Bước 3 – Ghép CFG với unit

Theo (file, tên đầy đủ đã bỏ tham số template, danh sách tham số).

| Lần chạy | Unit có CFG | Vấn đề | Xử lý |
|---|---|---|---|
| 1 | 1272 / 1540 (82.6%) | Hàm trong namespace ẩn danh: libclang ghi `(anonymous)`, Clang ghi `(anonymous namespace)` – và script tách nhầm dấu `(` của `(anonymous namespace)` làm danh sách tham số | Chuẩn hoá tên; che `(anonymous namespace)` trước khi tách tham số |
| 2 | 1437 / 1540 (93.3%) | Template chỉ có CFG khi được **instantiate**, file `.cc` được chọn cho unit không instantiate | Chạy Clang trên **tất cả 292 file `.cc`** (kể cả test – nơi hay instantiate template) |
| 3 | **1510 / 1540 (98.1%)** | 30 unit còn lại: template **không được instantiate ở đâu** trong Ceres (27 không có nhánh) | Prompt của 30 unit này tự chuyển sang "LLM tự dựng CFG" |

## Bước 4 – Đổi định dạng: đánh số node 1, 2, 3… riêng cho từng unit

**Vì sao:** bản đầu giữ tên khối của Clang (`B10` … `B0`). Clang dựng CFG **từ cuối hàm ngược lên**, nên số khối ngược thứ tự chạy (EXIT luôn là B0, ENTRY số lớn nhất) – khó đọc; prompt lại bắt LLM đổi sang tên khác (`N…`, `D…`) → 2 cách gọi cho cùng 1 node. Nhóm thống nhất **một cách gọi duy nhất**, độc lập với từng unit.

**Định dạng mới:**
- Đầu file: thông tin unit (mã, tên, file, dòng), chữ ký hàm theo Clang, số node, số điểm quyết định (QĐ), V(G).
- Node đánh số **1..n theo thứ tự chạy** (duyệt từ `START`, nhánh T trước); `START`, `END`, `DỪNG` (dừng do `CHECK`/`assert` sai).
- Mỗi dòng: `<số node>  [L<dòng>]  <nội dung>  <cạnh ra>`; node quyết định ghi `QĐ: <điều kiện>   T→x  F→y` (CHECK: `đúng→x  sai→DỪNG`).
- Khối rỗng / nội bộ (CHECK đúng đi tiếp, biến ẩn của for-range, phần nội bộ của VLOG) **gộp vào node kế tiếp**; khối "sau CHECK sai" (không tới được) **bỏ hẳn**.
- LLM dùng **đúng số node này** trong mọi bảng trả lời (đã sửa prompt mục 2.1, 2.4, 3, 4, 5, 6).

Kèm theo: tìm dòng cho vế trái của `&&`/`||` (bỏ phần `|| ...` trước khi so), hàm viết trên 1 dòng thì gán luôn dòng đó.

**Trường hợp bất thường (5 unit):** hàm dùng `assert(...)`, `LOG(FATAL)` hoặc luôn dừng – Clang dựng CFG mà mọi nhánh của 1 điểm quyết định đều về `DỪNG`. → Không đưa CFG dễ gây hiểu sai vào prompt; để LLM tự dựng từ mã nguồn. Nhận diện thêm `__assert_fail` (assert của C) như `CHECK`.

## Bước 5 – Viết CFG đơn giản hơn cho người đọc

**Vì sao:** bản ở Bước 4 vẫn rối: dòng "Hàm theo Clang: ceres::AutoDiffFirstOrderFunction<ceres::internal::QuadraticCostFunctor, 4>::NumParameters()" khó hiểu; nhãn `QĐ`, `CHECK`, `VLOG`, "vế trái", `V(G)` cần biết trước mới đọc được.

**Đã sửa:**
- **Phần đầu** lấy từ `units/<id>/info.json` (đã bổ sung từ `graph.db`): tên hàm + tham số (không có thì `()`), kiểu trả về, loại hàm (method / constructor / hàm tự do…), class hoặc namespace, vị trí. Bỏ dòng "Hàm theo Clang"; với template thêm 1 dòng **Ghi chú** giải thích bằng lời và chỉ ra chỗ dùng cụ thể (đã bỏ bớt `ceres::`, `internal::`).
- **Gộp sẵn** `a && b` / `a || b` thành 1 node (trước chỉ đánh dấu "vế trái").
- **Bỏ hẳn** các nhánh của `VLOG` (in log, không phải logic của hàm) và khối in log.
- Bỏ `QĐ`, `V(G)`; dùng `đúng → x   sai → y`; `dòng 193` thay `[L193]`; `vòng for, điều kiện: i < n` thay `for (...; i < n; ...)`; căn cột cho dễ nhìn.
- "(anonymous)" → "(namespace không tên)".

## Bước 6 – Sửa lỗi ghép nhầm overload, bỏ số dòng, không cắt câu lệnh

**Lỗi phát hiện khi xem u0018** (`BiCubicInterpolator::Evaluate(r, c, f)` – 3 tham số): cfg.txt lại là CFG của `Evaluate` 5 tham số. Lý do: bản 3 tham số không được dùng ở đâu trong Ceres nên Clang không dựng CFG; script không tìm được overload khớp thì **lấy đại ứng viên đầu tiên**.

**Đã sửa:**
- Ghép overload theo: số tham số (đếm từ mã nguồn, không đếm dấu phẩy trong `<...>`), tên tham số, hàm có phải template không. Không khớp → **không có CFG** (LLM tự dựng), không lấy đại. Kết quả: 14 unit trước đây bị ghép nhầm nay để LLM tự dựng (u0017, u0018, u0144–u0147, các move constructor u0615/u0621/u0623/u0640, u0674, u1023, u1083, u1084).
- `info.json`: hàm template không có tham số trong graph.db → đọc tham số từ mã nguồn (trước đây hiện sai là `()`). Hàm sinh từ macro ghi "xem mã nguồn".
- **Bỏ cột số dòng** (`dòng 193`, `dòng ?`): không cần cho việc thiết kế test path; `dòng ?` gây khó hiểu.
- **Không cắt câu lệnh** (trước cắt ở ~90 ký tự, để lại `p0.d…`). Node nhiều câu lệnh: mỗi câu 1 dòng.
- Câu lệnh chạy trước điều kiện (cùng khối Clang) trước đây in thành 1 dòng không có số → nay là **1 node có số**.
- Dòng **Ghi chú** của template viết lại: nói rõ CFG dựng với kiểu nào, gồm cả kiểu của hàm template (vd. `Make1stOrderPerturbations<integer_sequence<int, 2, 2>>::Apply<double, Jet<double, 4>>`).
- Thêm `--reuse`: dùng lại kết quả Clang (`data/.cfg_cache.pkl`, không commit) để chạy lại phần ghép trong ~20 s.

## Bước 7 – `info.json` dễ đọc, số nhánh đếm theo CFG

- Thay `branches`/`cyclomatic` của libclang (đếm cả `&&`, `||`, `CHECK`) bằng số liệu đếm trên CFG như người đếm: `cfg.decisions` (điểm rẽ nhánh), `cfg.branches` (số nhánh – mẫu số C2), `cfg.loops`, `cfg.checks`. Ví dụ u0540: libclang 8 nhánh → CFG 2 điểm rẽ nhánh, 4 nhánh, 1 CHECK.
- Thêm `signature`, `loc`, `how_to_call`, `template_example`; đổi `level` → `input_difficulty`, `topo_level` → `call_level`, `called_by_tests` → `existing_tests`; bỏ `callable`, `template_args`.
- Tổng (1491 unit có CFG): 1698 điểm rẽ nhánh, **3430 nhánh**, 562 vòng lặp, 498 CHECK (libclang: 5754 nhánh).
- Giải thích từng trường: `docs/phase4-guide.md` mục `info.json`.

## Kết quả

| Chỉ số | Giá trị |
|---|---|
| Unit có CFG | **1491 / 1540 (96.8%)** – 30 template không được dùng ở đâu + 14 overload không được dùng ở đâu + 5 CFG bất thường → LLM tự dựng |
| Thời gian | ~3.5 phút (292 file `.cc`, 4 luồng) |
| Node | 6422 |
| Điểm rẽ nhánh | 1698 (+ 498 lệnh CHECK) |
| Prompt đã ghép lại | 1540 (1491 có CFG, 49 để LLM tự dựng); 6.7–42 KB, trung vị ~7.9 KB |

Ví dụ (`units/u0540/cfg.txt`, phần CFG – định dạng đầy đủ ở `docs/phase4-guide.md`):
```
Số điểm rẽ nhánh: 2 (và 1 lệnh CHECK)

START → 1
1   CHECK_LT(index, size_)                                         đúng → 2   sai → DỪNG
2   if (upper_bound >= std::numeric_limits<double>::max() && !upper_bounds_)   đúng → 3   sai → 4
3   return                                                         → END
4   if (!upper_bounds_)                                            đúng → 5   sai → 6
5   upper_bounds_ = std::make_unique<double[]>(size_)
    std::fill(upper_bounds_.get(), upper_bounds_.get() + size_, std::numeric_limits<double>::max())   → 6
6   upper_bounds_[index] = upper_bound                             → END
```

Chỉ lưu bản đã làm gọn (`units/<id>/cfg.txt`), không lưu output thô. Danh sách unit không có CFG: `reports/cfg/summary.txt`. Log chạy: `logs/raw/build_cfg.log`.

## Hạn chế còn lại

- **Template:** CFG lấy từ **một** bản instantiate (vd. `AutoDiffCostFunction<BinaryScalarCost, 1, 2, 2>`), ghi rõ ở dòng **Ghi chú** của phần đầu.
