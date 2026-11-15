// FILE: u0409_test.cc
#include "gtest/gtest.h"
#include "ceres/scoped_thread_token.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0409, PathP1) {
  ceres::internal::ScopedThreadToken target;
  target.token();
}
