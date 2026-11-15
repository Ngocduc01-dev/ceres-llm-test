# Unit u0330

## Test path

The unit has a single straight-line path (no control-flow branches). The test invokes the API with a valid construction, including concrete adapters where the production type is abstract, and exercises the target declaration.

## Test source

```cpp
#include "gtest/gtest.h"
#include "ceres/linear_operator.h"

class Unit0330Operator final : public ceres::internal::LinearOperator {
 public:
  ~Unit0330Operator() override = default;
  void RightMultiplyAndAccumulate(const double*, double*) const override {}
  void LeftMultiplyAndAccumulate(const double*, double*) const override {}
  int num_rows() const override { return 0; }
  int num_cols() const override { return 0; }
};

TEST(Unit_u0330, PathP1) {
  { Unit0330Operator target; }
}
```
