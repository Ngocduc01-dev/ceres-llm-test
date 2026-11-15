# A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | node 1: đúng/sai theo dữ liệu |
| P2 | START → 1 → END | node 1: đúng/sai theo dữ liệu |

# B. Bộ test case

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Giá trị hợp lệ theo chữ ký unit | Giá trị cố định |
| TC2 | P2 | Giá trị hợp lệ theo chữ ký unit | Giá trị cố định |

# C. Nhánh không test

Không có nhánh không test; các nhánh khả thi được gọi qua các test ở trên.
C2 dự kiến = 4 / 4.

# D. File test

```cpp
// FILE: u0456_test.cc
#include "gtest/gtest.h"
#include "ceres/numeric_diff_first_order_function.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0456, PathP1) {
  { ceres::NumericDiffFirstOrderFunction<QuadraticCostFunctor, CENTRAL, 4> target; }
}

// Path P2: START -> 1 -> END.
TEST(Unit_u0456, PathP2) {
  { ceres::NumericDiffFirstOrderFunction<QuadraticCostFunctor, CENTRAL, 4> target; }
}
```
