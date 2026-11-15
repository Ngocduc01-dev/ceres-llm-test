// FILE: u0497_test.cc
#include <sstream>
#include "gtest/gtest.h"
#include "ceres/jet.h"
TEST(Unit_u0497, StreamInsertion) {
  std::ostringstream stream;
  ceres::Jet<double, 2> value(1.0);
  stream << value;
}
