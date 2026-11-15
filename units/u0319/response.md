# Unit u0319

## Test path

The unit has a single straight-line path (no control-flow branches). The test invokes the API with a valid construction, including concrete adapters where the production type is abstract, and exercises the target declaration.

## Test source

```cpp
#include "gtest/gtest.h"
#include "ceres/iterative_refiner.h"

TEST(Unit_u0319, PathP1) {
  { ceres::internal::DenseIterativeRefiner target(1); }
}
```
