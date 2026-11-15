// FILE: u0218_test.cc
#include "gtest/gtest.h"
#include "ceres/tiny_solver_autodiff_function.h"

namespace {

// Functor có số residual động: NumResiduals() do functor cung cấp.
struct DynamicResidualsFunctor {
  int NumResiduals() const { return 2; }

  template <typename T>
  bool operator()(const T* parameters, T* residuals) const {
    residuals[0] = parameters[0] + parameters[1];
    residuals[1] = parameters[2] - parameters[0];
    return true;
  }
};

}  // namespace

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(TinySolverAutoDiffFunctionNumResiduals, ReturnsNumResidualsP1) {
  DynamicResidualsFunctor functor;
  ceres::TinySolverAutoDiffFunction<DynamicResidualsFunctor, -1, 3> function(
      functor);
  function.NumResiduals();
}
