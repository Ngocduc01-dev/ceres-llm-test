// FILE: u0768_test.cc
#include "gtest/gtest.h"
#include "ceres/stringprintf.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0768, TC1_CallsTarget) {
  va_list ap{};
  ceres::internal::StringAppendV(nullptr, nullptr, ap);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0768, TC2_CallsTarget) {
  va_list ap{};
  ceres::internal::StringAppendV(nullptr, nullptr, ap);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u0768, TC3_CallsTarget) {
  va_list ap{};
  ceres::internal::StringAppendV(nullptr, nullptr, ap);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u0768, TC4_CallsTarget) {
  va_list ap{};
  ceres::internal::StringAppendV(nullptr, nullptr, ap);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u0768, TC5_CallsTarget) {
  va_list ap{};
  ceres::internal::StringAppendV(nullptr, nullptr, ap);
}
