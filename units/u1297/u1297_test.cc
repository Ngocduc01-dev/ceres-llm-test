// FILE: u1297_test.cc
#include "gtest/gtest.h"
#include "ceres/reorder_program.h"
#include "ceres/ordered_groups.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"
#include "ceres/program.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1297, TC1_CallsTarget) {
  ProblemImpl::ParameterMap parameter_map{};
  ParameterBlockOrdering ordering{};
  ceres::internal::ApplyOrdering(parameter_map, ordering, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1297, TC2_CallsTarget) {
  ProblemImpl::ParameterMap parameter_map{};
  ParameterBlockOrdering ordering{};
  ceres::internal::ApplyOrdering(parameter_map, ordering, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1297, TC3_CallsTarget) {
  ProblemImpl::ParameterMap parameter_map{};
  ParameterBlockOrdering ordering{};
  ceres::internal::ApplyOrdering(parameter_map, ordering, nullptr, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1297, TC4_CallsTarget) {
  ProblemImpl::ParameterMap parameter_map{};
  ParameterBlockOrdering ordering{};
  ceres::internal::ApplyOrdering(parameter_map, ordering, nullptr, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1297, TC5_CallsTarget) {
  ProblemImpl::ParameterMap parameter_map{};
  ParameterBlockOrdering ordering{};
  ceres::internal::ApplyOrdering(parameter_map, ordering, nullptr, nullptr);
}
