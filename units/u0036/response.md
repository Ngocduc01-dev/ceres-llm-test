**A. Test paths**

Hàm `begin()` không có điểm rẽ nhánh nào (0 điểm rẽ nhánh, 0 nhánh). Chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Kích thước mảng n: 1 đến 5 (không có điều kiện ràng buộc; `FixedArray<double>` được tạo với n phần tử) | n = 3 (chọn ngẫu nhiên cố định trong khoảng 1..5) |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh nên không có nhánh nào bị bỏ qua, và `CHECK` không xuất hiện trong hàm này.

C2 dự kiến = 0 / 0 (hàm không có nhánh; test chỉ phủ node 1, tức đạt C1 đầy đủ).

**D. File test**

```cpp
// FILE: u0036_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(FixedArrayBeginTest, TC1_P1_BeginOnNonEmptyArray) {
  const ceres::internal::FixedArray<double>::size_type n = 3;
  ceres::internal::FixedArray<double> array(n);
  ceres::internal::FixedArray<double>::iterator it = array.begin();
  (void)it;
}
```