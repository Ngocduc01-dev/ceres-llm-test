# Unit u0306

## Test path

The unit has a single straight-line path (no control-flow branches). The test invokes the API with a valid construction, including concrete adapters where the production type is abstract, and exercises the target declaration.

## Test source

```cpp
#include "gtest/gtest.h"
#include "ceres/first_order_function.h"
#include "ceres/gradient_problem.h"
#include "ceres/gradient_problem_evaluator.h"

class Unit0306Function final : public ceres::FirstOrderFunction {
 public:
  int NumParameters() const override { return 1; }
  bool Evaluate(const double*, double* cost, double* gradient) const override {
    *cost = 0.0;
    if (gradient != nullptr) { gradient[0] = 0.0; }
    return true;
  }
};

TEST(Unit_u0306, PathP1) {
  ceres::GradientProblem problem(new Unit0306Function);
  ceres::internal::GradientProblemEvaluator target(problem);
  EXPECT_EQ(target.NumResiduals(), 1);
}
```
