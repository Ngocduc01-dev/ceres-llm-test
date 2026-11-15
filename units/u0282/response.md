# Unit u0282

## Test path

The unit has a single straight-line path (no control-flow branches). The test supplies the required concrete linear solver through `TrustRegionStrategy::Options`, constructs the strategy, and invokes the target API.

## Test source

```cpp
#include "gtest/gtest.h"
#include "ceres/dogleg_strategy.h"

TEST(Unit_u0282, PathP1) {
  ceres::internal::TrustRegionStrategy::Options options;
  ceres::internal::LinearSolver::Options solver_options;
  auto linear_solver = ceres::internal::LinearSolver::Create(solver_options);
  options.linear_solver = linear_solver.get();
  ceres::internal::DoglegStrategy target(options);
  target.StepIsInvalid();
}
```
