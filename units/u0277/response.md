# Unit u0277

## Test path

The unit has a single straight-line path (no control-flow branches). The test invokes the API with a valid construction, including concrete adapters where the production type is abstract, and exercises the target declaration.

## Test source

```cpp
#include "gtest/gtest.h"
#include "ceres/dense_cholesky.h"
#include "ceres/iterative_refiner.h"
#include <memory>

TEST(Unit_u0277, PathP1) {
  ceres::internal::RefinedDenseCholesky target(
      std::make_unique<ceres::internal::EigenDenseCholesky>(),
      std::make_unique<ceres::internal::DenseIterativeRefiner>(1));
}
```
