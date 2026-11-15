# Unit u0317

## Test path

The unit has a single straight-line path (no control-flow branches). The test invokes the API with a valid construction, including concrete adapters where the production type is abstract, and exercises the target declaration.

## Test source

```cpp
#include "gtest/gtest.h"
#include "ceres/iterative_refiner.h"

TEST(Unit_u0317, PathP1) {
  { ceres::internal::SparseIterativeRefiner target(1); }
}
```
