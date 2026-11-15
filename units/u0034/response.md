**A. Test paths**

Hàm có 0 điểm rẽ nhánh, CFG chỉ có một đường đi duy nhất (node 1 là câu lệnh `return *(end() - 1)`).

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Kích thước mảng n trong [1, 5] (n ≥ 1 để `end() - 1` hợp lệ); giá trị phần tử là int bất kỳ | n = 3 (chọn từ seed cố định), giá trị phần tử = 7 |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh và không có `CHECK`, nên không có nhánh nào bị bỏ.

`C2 dự kiến = 0 / 0` (tổng số nhánh = 0; chỉ cần đi qua node 1 một lần, tức là mọi lệnh đều chạy, độ phủ C2 coi như 100%).

**D. File test**

```cpp
// FILE: u0034_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(FixedArrayBackTest, TC1_BackOnNonEmptyArray) {
  // n = 3 nằm trong [1, 5]; giá trị khởi tạo cố định = 7
  ceres::internal::FixedArray<int, 12> array(3, 7);
  // Gọi unit một lần, không kiểm tra kết quả trả về
  ceres::internal::FixedArray<int, 12>::reference r = array.back();
  (void)r;
}
```