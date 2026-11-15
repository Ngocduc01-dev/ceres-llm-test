# Unit u0485
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
// FILE: u0485_test.cc
#include "gtest/gtest.h"
#include "ceres/problem_impl.h"

// P1: START -> 1 (CHECK đúng) -> END
// Path P1: START -> CFG nodes -> END.
TEST(ProblemImplResidualBlockSet, FastRemovalEnabled) {
  ceres::Problem::Options options;
  options.enable_fast_removal = true;
  ceres::internal::ProblemImpl problem(options);
  problem.residual_block_set();
}
```
