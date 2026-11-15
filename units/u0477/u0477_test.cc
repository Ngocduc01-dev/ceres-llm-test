// FILE: u0477_test.cc
#include <mutex>
#include "gtest/gtest.h"
#include "ceres/parallel_for.h"
TEST(Unit_u0477, Lock) { std::mutex mutex; auto lock=ceres::internal::MakeConditionalLock(1,mutex); }
