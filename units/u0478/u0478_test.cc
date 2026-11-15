// FILE: u0478_test.cc
#include "gtest/gtest.h"
#include "ceres/parallel_invoke.h"

namespace ceres::internal {

// Path P1: START -> 1 -> 2 -> END (kPassThreadId = false, goi function(args...))
TEST(InvokeWithThreadIdTest, FunctionWithoutThreadId) {
  const int thread_id = 3;
  int value = 2;
  auto function = [](int& v) { v += 1; };
  InvokeWithThreadId(thread_id, function, value);
}

// Path P2: START -> 1 -> END (kPassThreadId = true, goi function(thread_id, args...))
TEST(InvokeWithThreadIdTest, FunctionWithThreadId) {
  const int thread_id = 1;
  int value = 4;
  auto function = [](int tid, int& v) { v += tid; };
  InvokeWithThreadId(thread_id, function, value);
}

}  // namespace ceres::internal
