// FILE: u0654_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"

// Path P1 calls set_storage_type(const StorageType storage_type).
TEST(Unitu0654, CallsTarget) {
  object.set_storage_type({});
}
