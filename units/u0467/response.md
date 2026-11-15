# Unit u0467
## A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → END | Không có điểm rẽ nhánh. |

## B. Bộ test case

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |

## C. Nhánh không test

Không có nhánh điều khiển trong CFG.
C2 dự kiến = 0 / 0.

## D. File test

```cpp
// FILE: u0467_test.cc
#include "gtest/gtest.h"
#include "ceres/levenberg_marquardt_strategy.h"

namespace ceres {
namespace internal {

// TC1 - P1: START -> 1 (CHECK_GT đúng) -> 2 -> END
// Path P1: START -> CFG nodes -> END.
TEST(LevenbergMarquardtStrategyStepAcceptedTest, P1_PositiveStepQuality) {
  LinearSolver::Options linear_solver_options;
  linear_solver_options.type = DENSE_QR;
  std::unique_ptr<LinearSolver> linear_solver(
      LinearSolver::Create(linear_solver_options));

  TrustRegionStrategy::Options options;
  options.linear_solver = linear_solver.get();
  options.initial_radius = 1e4;
  options.max_radius = 1e8;
  options.min_lm_diagonal = 1e-6;
  options.max_lm_diagonal = 1e32;

  LevenbergMarquardtStrategy strategy(options);
  strategy.StepAccepted(0.7);
}

}  // namespace internal
}  // namespace ceres
```
