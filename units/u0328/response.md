# Unit u0328

## Test path

The unit has a single straight-line path (no control-flow branches). The test invokes the API with a valid construction, including concrete adapters where the production type is abstract, and exercises the target declaration.

## Test source

```cpp
#include "gtest/gtest.h"
#include "ceres/line_search_minimizer.h"

TEST(Unit_u0328, PathP1) {
  ceres::internal::LineSearchMinimizer::State target(1, 1);
  EXPECT_EQ(target.gradient.size(), 1);
  EXPECT_EQ(target.search_direction.size(), 1);
}
```
