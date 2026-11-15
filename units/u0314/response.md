# Unit u0314

## Test path

The unit has a single straight-line path (no control-flow branches). The test invokes the API with a valid construction, including concrete adapters where the production type is abstract, and exercises the target declaration.

## Test source

```cpp
#include "gtest/gtest.h"
#include "ceres/implicit_schur_complement.h"

TEST(Unit_u0314, PathP1) {
  ceres::internal::LinearSolver::Options options;
  ceres::internal::ImplicitSchurComplement target(options);
  EXPECT_TRUE(target.rhs().size() == 0);
}
```
