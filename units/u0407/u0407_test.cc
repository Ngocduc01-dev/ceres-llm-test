// FILE: u0407_test.cc
#include "gtest/gtest.h"
#include "ceres/schur_eliminator.h"
#include "ceres/schur_eliminator_impl.h"
#include "ceres/stl_util.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(SchurEliminatorDestructorTest, DestroyWithoutInit) {
  ContextImpl context;
  LinearSolver::Options options;
  options.num_threads = 1;
  options.context = &context;

  auto* eliminator = new SchurEliminator<2, 2, 2>(options);
  delete eliminator;  // gọi ~SchurEliminator() đúng một lần
}

}  // namespace internal
}  // namespace ceres
