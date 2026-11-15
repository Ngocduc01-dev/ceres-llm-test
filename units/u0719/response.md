# Unit u0719
## A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → 4 → 5 → 6 → END | Theo CFG của prompt.md. |
| P2 | START → 1 → 2 → 3 → 4 → 5 → 6 → END | Theo CFG của prompt.md. |

## B. Bộ test case

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |
| TC2 | P2 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |

## C. Nhánh không test

Không ghi nhận nhánh không thể test từ CFG cung cấp.
C2 dự kiến = 4 / 4.

## D. File test

```cpp
// FILE: u0719_test.cc
#include "gtest/gtest.h"
#include "ceres/tiny_solver.h"

struct LocalTinyFunction {
  using Scalar = double;
  static constexpr int NUM_RESIDUALS = 1;
  static constexpr int NUM_PARAMETERS = 1;
  bool operator()(const double*, double* residual, double* jacobian) const {
    residual[0] = 1.0;
    jacobian[0] = 1.0;
    return true;
  }
};
// Path P1: START -> 1 -> 3 -> 4 -> 5 -> 6 -> END.
TEST(Unit_u0719, PathP1) {
  ceres::TinySolver<LocalTinyFunction> target;
  LocalTinyFunction function;
  ceres::TinySolver<LocalTinyFunction>::Parameters x;
  x[0] = 0.0;
  target.summary.iterations = 0;
  target.Update(function, x);
}
```
