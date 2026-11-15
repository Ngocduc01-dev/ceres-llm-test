# Unit u0310

## Test path

The unit has a single straight-line path (no control-flow branches). The test uses the concrete/public API required by the declaration and invokes the target.

## Test source

```cpp
#include "gtest/gtest.h"
#include "ceres/graph.h"

TEST(Unit_u0310, PathP1) {
  ceres::internal::WeightedGraph<int> target;
  EXPECT_TRUE(target.vertices().empty());
}
```
