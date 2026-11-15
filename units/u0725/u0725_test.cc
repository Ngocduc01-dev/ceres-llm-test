// FILE: u0725_test.cc
#include "gtest/gtest.h"
#include "ceres/file.h"#include <string>

#include <cstdint>

namespace ceres {
namespace internal {
// Path P1 calls ReadFileToStringOrDie(const std::string & filename, std::string * data).
TEST(Unitu0725, CallsTarget) {
  double data_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  ReadFileToStringOrDie(std::string(), data_data);
}
}  // namespace internal
}  // namespace ceres
