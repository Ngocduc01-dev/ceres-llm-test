// FILE: u0379_test.cc
#include "gtest/gtest.h"
#include "ceres/power_series_expansion_preconditioner.h"

namespace ceres {
namespace internal {

// P1: START -> END (destructor không có điểm rẽ nhánh)
TEST(PowerSeriesExpansionPreconditionerDestructorTest, TC1_P1_StartToEnd) {
  const ImplicitSchurComplement* isc = nullptr;
  const int max_num_spse_iterations = 3;
  const double spse_tolerance = 0.01;
  Preconditioner::Options options;

  // Destructor được gọi đúng một lần khi đối tượng bị huỷ.
  PowerSeriesExpansionPreconditioner* preconditioner =
      new PowerSeriesExpansionPreconditioner(
          isc, max_num_spse_iterations, spse_tolerance, options);
  delete preconditioner;
}

}  // namespace internal
}  // namespace ceres
