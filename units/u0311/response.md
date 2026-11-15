# Unit u0311

## Test path

The unit has a single straight-line path (no control-flow branches). The test uses the concrete/public API required by the declaration and invokes the target.

## Test source

```cpp
#include "gtest/gtest.h"
#include "ceres/graph.h"
#include <cmath>

TEST(Unit_u0311, PathP1) {
  EXPECT_TRUE(std::isnan(ceres::internal::WeightedGraph<int>::InvalidWeight()));
}
```
