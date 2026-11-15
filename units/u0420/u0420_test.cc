// FILE: u0420_test.cc
#include "gtest/gtest.h"
#include "ceres/suitesparse.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (node 1: return false)
TEST(SuiteSparseIsNestedDissectionAvailable, TC1_ReturnFalsePath) {
  SuiteSparse obj;
  obj.IsNestedDissectionAvailable();
}

}  // namespace internal
}  // namespace ceres
