# Unit u0656
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
// FILE: u0656_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_cholesky.h"
#include "ceres/iterative_refiner.h"
#include <memory>

// Path P1: START -> 1 -> END.
TEST(Unit_u0656, PathP1) {
  std::unique_ptr<ceres::internal::DenseCholesky> dense_cholesky;
  std::unique_ptr<ceres::internal::DenseIterativeRefiner> iterative_refiner;
  ceres::internal::RefinedDenseCholesky target(std::move(dense_cholesky), std::move(iterative_refiner));
}
```
