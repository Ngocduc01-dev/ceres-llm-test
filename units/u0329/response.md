# Unit u0329

## Test path

The unit has a single straight-line path (no control-flow branches). The test invokes the API with a valid construction, including concrete adapters where the production type is abstract, and exercises the target declaration.

## Test source

```cpp
#include "gtest/gtest.h"
#include "ceres/linear_least_squares_problems.h"

TEST(Unit_u0329, PathP1) {
  ceres::internal::LinearLeastSquaresProblem target;
  EXPECT_EQ(target.num_eliminate_blocks, 0);
}
```
