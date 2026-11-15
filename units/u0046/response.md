**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm rẽ nhánh, tổng số nhánh = 0). Chỉ có một đường đi duy nhất. Mã nguồn khớp với CFG. Lời gọi `std::fill(begin(), end(), val)` là lời gọi thư viện chuẩn, không tính là điểm rẽ nhánh của unit.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

Hàm không có vòng lặp trong mã của unit nên không áp dụng quy tắc số lần lặp. Đầu vào là `val` (kiểu `int`) và kích thước mảng. Chọn mảng có 3 phần tử (khoảng 1 đến 5) để `std::fill` ghi vào nhiều hơn một phần tử.

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | kích thước mảng n ∈ [1, 5]; val ∈ [-10, 10] (seed cố định, chọn ngẫu nhiên một lần) | n = 3, val = 7 |

**C. Nhánh không test**

Không có nhánh nào bị bỏ qua. Không có nhánh `CHECK`.

`C2 dự kiến = 0 / 0` (hàm không có điểm rẽ nhánh nên không có nhánh nào để tính, test vẫn chạy toàn bộ đường đi duy nhất START → 1 → END).

**D. File test**

```cpp
// FILE: u0046_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(FixedArrayFill, SinglePath) {
  ceres::internal::FixedArray<int, 20> arr(3);
  arr.fill(7);
}
```