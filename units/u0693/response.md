# Unit u0693
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
// FILE: u0693_test.cc
#include "gtest/gtest.h"
#include "ceres/iterative_refiner.h"
#include "ceres/sparse_cholesky.h"
#include <memory>

// Path P1: START -> 1 -> END.
TEST(Unit_u0693, PathP1) {
  std::unique_ptr<ceres::internal::SparseCholesky> sparse_cholesky;
  std::unique_ptr<ceres::internal::SparseIterativeRefiner> iterative_refiner;
  ceres::internal::RefinedSparseCholesky target(std::move(sparse_cholesky), std::move(iterative_refiner));
}
```
