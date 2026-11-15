// FILE: u0544_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/memory.h"
#include <memory>

// Path P1: START -> 1 -> 2 -> 3 -> 4 -> 5 -> 2 -> END.
TEST(Unit_u0544, PathP1) {
  std::allocator<double> alloc;
  alignas(double) unsigned char storage[sizeof(double)];
  double* first = reinterpret_cast<double*>(storage);
  ceres::internal::ConstructRange(alloc, first, first + 1, 1.0);
  std::allocator_traits<std::allocator<double>>::destroy(alloc, first);
}
