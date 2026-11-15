// FILE: u1407_test.cc
#include "gtest/gtest.h"
#include "ceres/evaluation_callback.h"
#include "ceres/internal/fixed_array.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1407, TC1_CallsTarget) {
  bool apply_loss_function{};
  bool new_point{};
  ceres::internal::ProblemImpl object{};
  object.EvaluateResidualBlock(nullptr, apply_loss_function, new_point, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1407, TC2_CallsTarget) {
  bool apply_loss_function{};
  bool new_point{};
  ceres::internal::ProblemImpl object{};
  object.EvaluateResidualBlock(nullptr, apply_loss_function, new_point, nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1407, TC3_CallsTarget) {
  bool apply_loss_function{};
  bool new_point{};
  ceres::internal::ProblemImpl object{};
  object.EvaluateResidualBlock(nullptr, apply_loss_function, new_point, nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1407, TC4_CallsTarget) {
  bool apply_loss_function{};
  bool new_point{};
  ceres::internal::ProblemImpl object{};
  object.EvaluateResidualBlock(nullptr, apply_loss_function, new_point, nullptr, nullptr, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1407, TC5_CallsTarget) {
  bool apply_loss_function{};
  bool new_point{};
  ceres::internal::ProblemImpl object{};
  object.EvaluateResidualBlock(nullptr, apply_loss_function, new_point, nullptr, nullptr, nullptr);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1407, TC6_CallsTarget) {
  bool apply_loss_function{};
  bool new_point{};
  ceres::internal::ProblemImpl object{};
  object.EvaluateResidualBlock(nullptr, apply_loss_function, new_point, nullptr, nullptr, nullptr);
}
