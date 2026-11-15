// FILE: u0491_test.cc
#include "gtest/gtest.h"
#include "ceres/thread_token_provider.h"
TEST(Unit_u0491, Acquire) { ceres::internal::ThreadTokenProvider target(1); auto token=target.Acquire(); }
