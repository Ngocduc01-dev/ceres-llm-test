# Unit u0331

## Test path

The unit has a single straight-line path (no control-flow branches). The test invokes the API with a valid construction, including concrete adapters where the production type is abstract, and exercises the target declaration.

## Test source

```cpp
#include "gtest/gtest.h"
#include "ceres/linear_solver.h"

class Unit0331Solver final : public ceres::internal::LinearSolver {
 public:
  Summary Solve(LinearOperator*, const double*, const PerSolveOptions&, double*) override {
    return {};
  }
};

TEST(Unit_u0331, PathP1) {
  Unit0331Solver target;
  EXPECT_TRUE(target.Statistics().empty());
}
```
