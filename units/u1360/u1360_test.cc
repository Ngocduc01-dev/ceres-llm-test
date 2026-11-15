// FILE: u1360_test.cc
#include "gtest/gtest.h"
#include "ceres/thread_pool.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1360, TC1_CallsTarget) {
  int num_threads{};
  ceres::internal::ThreadPool object{};
  object.Resize(num_threads);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1360, TC2_CallsTarget) {
  int num_threads{};
  ceres::internal::ThreadPool object{};
  object.Resize(num_threads);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1360, TC3_CallsTarget) {
  int num_threads{};
  ceres::internal::ThreadPool object{};
  object.Resize(num_threads);
}
