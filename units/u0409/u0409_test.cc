// FILE: u0409_test.cc
#include "gtest/gtest.h"
#include "ceres/scoped_thread_token.h"
#include "ceres/thread_token_provider.h"
// Path P1: START -> 1 -> END.
TEST(Unit_u0409, PathP1) { ceres::internal::ThreadTokenProvider provider(1); ceres::internal::ScopedThreadToken target(&provider); target.token(); }
