// FILE: u0768_test.cc
#include "gtest/gtest.h"
#include "ceres/stringprintf.h"

// P1: START -> 1 -> END
TEST(StringAppendVTest, TC1_CallsTarget) {
  char a1[8] = {};
  va_list a2{};
  ceres::internal::StringAppendV(nullptr, a1, a2);
}

// P2: START -> 1 -> END
TEST(StringAppendVTest, TC2_CallsTarget) {
  char a1[8] = {};
  va_list a2{};
  ceres::internal::StringAppendV(nullptr, a1, a2);
}

// P3: START -> 1 -> END
TEST(StringAppendVTest, TC3_CallsTarget) {
  char a1[8] = {};
  va_list a2{};
  ceres::internal::StringAppendV(nullptr, a1, a2);
}

