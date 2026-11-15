# Unit u0324

## Test path

The unit has a single straight-line path (no control-flow branches). The test invokes the API with a valid construction, including concrete adapters where the production type is abstract, and exercises the target declaration.

## Test source

```cpp
#include "gtest/gtest.h"
#include "ceres/line_search.h"

TEST(Unit_u0324, PathP1) {
  ceres::internal::LineSearchFunction target(nullptr);
  EXPECT_DOUBLE_EQ(target.DirectionInfinityNorm(), 0.0);
}
```
