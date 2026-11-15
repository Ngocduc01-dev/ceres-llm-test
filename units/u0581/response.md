# Unit u0581
## A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh. |

## B. Bộ test case

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |

## C. Nhánh không test

Không có nhánh điều khiển trong CFG.
C2 dự kiến = 0 / 0.

## D. File test

```cpp
// FILE: u0581_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.cc"

namespace ceres {
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0581, CallsTarget) {
  double x_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double jacobian_ptr_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  QuaternionPlusJacobianImpl(x_data, jacobian_ptr_data);
}
}  // namespace ceres
```
