// FILE: u0710_test.cc
#include "gtest/gtest.h"
#include "ceres/file.h"#include <string>

namespace ceres {
namespace internal {
// Path P1 calls WriteStringToFileOrDie(const std::string & data, const std::string & filename).
TEST(Unitu0710, CallsTarget) {
  WriteStringToFileOrDie(std::string(), std::string());
}
}  // namespace internal
}  // namespace ceres
