// FILE: u0686_test.cc
#include "gtest/gtest.h"
#include "ceres/partitioned_matrix_view.h"

// Path P1 calls ~PartitionedMatrixViewBase().
TEST(Unitu0686, CallsTarget) {
  PartitionedMatrixViewBase object{};
}
