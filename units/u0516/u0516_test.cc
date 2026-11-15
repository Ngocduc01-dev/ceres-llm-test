// FILE: u0516_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/autodiff.h"

namespace ceres {
namespace internal {
// Path P1 calls Take1stOrderPart(const int M, const JetT* src, T* dst).
TEST(Unitu0516, CallsTarget) {
  double src_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double dst_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  Take1stOrderPart(1, src_data, dst_data);
}
}  // namespace internal
}  // namespace ceres
