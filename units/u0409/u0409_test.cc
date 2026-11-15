// FILE: u0409_test.cc
#include "gtest/gtest.h"
#include "ceres/scoped_thread_token.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ScopedThreadTokenTokenTest, P1_ReturnToken) {
  ThreadTokenProvider provider(3);
  ScopedThreadToken scoped_token(&provider);
  int value = scoped_token.token();
  (void)value;
}

}  // namespace internal
}  // namespace ceres
