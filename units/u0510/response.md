# Unit u0510
## A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → END | Không có điểm rẽ nhánh. |
| P2 | START → 1 → 2 → 3 → END | Không có điểm rẽ nhánh. |

## B. Bộ test case

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |
| TC2 | P2 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |

## C. Nhánh không test

Không có nhánh điều khiển trong CFG.
C2 dự kiến = 0 / 0.

## D. File test

```cpp
// FILE: u0510_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/eigen.h"
#include "ceres/small_blas.h"

namespace ceres {
namespace internal {
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0510, CallsTarget) {
  MatrixMatrixMultiplyEigen({});
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0510, CallsTargetAlternate) {
  MatrixMatrixMultiplyEigen({});
}
}  // namespace internal
}  // namespace ceres
```
