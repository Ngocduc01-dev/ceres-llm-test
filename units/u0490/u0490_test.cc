// FILE: u0490_test.cc
#include "gtest/gtest.h"
#include "ceres/thread_token_provider.h"
TEST(Unit_u0490, Constructor) { ceres::internal::ThreadTokenProvider target(1); }
