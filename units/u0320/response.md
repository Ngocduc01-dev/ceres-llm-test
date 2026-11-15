# Unit u0320

## Test path

The unit has a single straight-line path (no control-flow branches). The test invokes the API with a valid construction, including concrete adapters where the production type is abstract, and exercises the target declaration.

## Test source

```cpp
#include "gtest/gtest.h"
#include "ceres/iterative_schur_complement_solver.h"

TEST(Unit_u0320, PathP1) {
  ceres::internal::LinearSolver::Options options;
  { ceres::internal::IterativeSchurComplementSolver target(options); }
}
```
