// FILE: u0710_test.cc
#include "gtest/gtest.h"
#include "ceres/file.h"

namespace ceres {
namespace internal {
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0710, CallsTarget) {
  WriteStringToFileOrDie(std::string(), std::string());
}
}  // namespace internal
}  // namespace ceres
