// FILE: u0725_test.cc
#include "gtest/gtest.h"
#include "ceres/file.h"

namespace ceres {
namespace internal {
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0725, CallsTarget) {
  double data_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  ReadFileToStringOrDie(std::string(), data_data);
}
}  // namespace internal
}  // namespace ceres
