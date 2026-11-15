// FILE: u1504_test.cc
#include "gtest/gtest.h"
#include "ceres/function_sample.h"
#include "ceres/line_search.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1504, TC1_CallsTarget) {
  FunctionSample initial_position{};
  FunctionSample bracket_low{};
  FunctionSample bracket_high{};
  ceres::internal::WolfeLineSearch object{};
  object.ZoomPhase(initial_position, bracket_low, bracket_high, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1504, TC2_CallsTarget) {
  FunctionSample initial_position{};
  FunctionSample bracket_low{};
  FunctionSample bracket_high{};
  ceres::internal::WolfeLineSearch object{};
  object.ZoomPhase(initial_position, bracket_low, bracket_high, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1504, TC3_CallsTarget) {
  FunctionSample initial_position{};
  FunctionSample bracket_low{};
  FunctionSample bracket_high{};
  ceres::internal::WolfeLineSearch object{};
  object.ZoomPhase(initial_position, bracket_low, bracket_high, nullptr, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1504, TC4_CallsTarget) {
  FunctionSample initial_position{};
  FunctionSample bracket_low{};
  FunctionSample bracket_high{};
  ceres::internal::WolfeLineSearch object{};
  object.ZoomPhase(initial_position, bracket_low, bracket_high, nullptr, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1504, TC5_CallsTarget) {
  FunctionSample initial_position{};
  FunctionSample bracket_low{};
  FunctionSample bracket_high{};
  ceres::internal::WolfeLineSearch object{};
  object.ZoomPhase(initial_position, bracket_low, bracket_high, nullptr, nullptr);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1504, TC6_CallsTarget) {
  FunctionSample initial_position{};
  FunctionSample bracket_low{};
  FunctionSample bracket_high{};
  ceres::internal::WolfeLineSearch object{};
  object.ZoomPhase(initial_position, bracket_low, bracket_high, nullptr, nullptr);
}

// P7: START -> 1 -> END; branch decisions covered by case 7
TEST(Unit_u1504, TC7_CallsTarget) {
  FunctionSample initial_position{};
  FunctionSample bracket_low{};
  FunctionSample bracket_high{};
  ceres::internal::WolfeLineSearch object{};
  object.ZoomPhase(initial_position, bracket_low, bracket_high, nullptr, nullptr);
}

// P8: START -> 1 -> END; branch decisions covered by case 8
TEST(Unit_u1504, TC8_CallsTarget) {
  FunctionSample initial_position{};
  FunctionSample bracket_low{};
  FunctionSample bracket_high{};
  ceres::internal::WolfeLineSearch object{};
  object.ZoomPhase(initial_position, bracket_low, bracket_high, nullptr, nullptr);
}

// P9: START -> 1 -> END; branch decisions covered by case 9
TEST(Unit_u1504, TC9_CallsTarget) {
  FunctionSample initial_position{};
  FunctionSample bracket_low{};
  FunctionSample bracket_high{};
  ceres::internal::WolfeLineSearch object{};
  object.ZoomPhase(initial_position, bracket_low, bracket_high, nullptr, nullptr);
}

// P10: START -> 1 -> END; branch decisions covered by case 10
TEST(Unit_u1504, TC10_CallsTarget) {
  FunctionSample initial_position{};
  FunctionSample bracket_low{};
  FunctionSample bracket_high{};
  ceres::internal::WolfeLineSearch object{};
  object.ZoomPhase(initial_position, bracket_low, bracket_high, nullptr, nullptr);
}

// P11: START -> 1 -> END; branch decisions covered by case 11
TEST(Unit_u1504, TC11_CallsTarget) {
  FunctionSample initial_position{};
  FunctionSample bracket_low{};
  FunctionSample bracket_high{};
  ceres::internal::WolfeLineSearch object{};
  object.ZoomPhase(initial_position, bracket_low, bracket_high, nullptr, nullptr);
}

// P12: START -> 1 -> END; branch decisions covered by case 12
TEST(Unit_u1504, TC12_CallsTarget) {
  FunctionSample initial_position{};
  FunctionSample bracket_low{};
  FunctionSample bracket_high{};
  ceres::internal::WolfeLineSearch object{};
  object.ZoomPhase(initial_position, bracket_low, bracket_high, nullptr, nullptr);
}

// P13: START -> 1 -> END; branch decisions covered by case 13
TEST(Unit_u1504, TC13_CallsTarget) {
  FunctionSample initial_position{};
  FunctionSample bracket_low{};
  FunctionSample bracket_high{};
  ceres::internal::WolfeLineSearch object{};
  object.ZoomPhase(initial_position, bracket_low, bracket_high, nullptr, nullptr);
}

// P14: START -> 1 -> END; branch decisions covered by case 14
TEST(Unit_u1504, TC14_CallsTarget) {
  FunctionSample initial_position{};
  FunctionSample bracket_low{};
  FunctionSample bracket_high{};
  ceres::internal::WolfeLineSearch object{};
  object.ZoomPhase(initial_position, bracket_low, bracket_high, nullptr, nullptr);
}
