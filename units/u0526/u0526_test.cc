// FILE: u0526_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/eigen.h"
#include "ceres/invert_psd_matrix.h"

namespace ceres {
namespace internal {
// Path P1 calls InvertPSDMatrix(const bool assume_full_rank, const typename EigenTypes<kSize, kSize>::Matrix& m).
TEST(Unitu0526, CallsTarget) {
  InvertPSDMatrix(true, {});
}
}  // namespace internal
}  // namespace ceres
