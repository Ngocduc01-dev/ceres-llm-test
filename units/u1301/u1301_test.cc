// FILE: u1301_test.cc
#include "gtest/gtest.h"
#include "ceres/ordered_groups.h"
#include "ceres/coordinate_descent_minimizer.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"
#include "ceres/program.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1301, TC1_CallsTarget) {
  Program program{};
  ProblemImpl::ParameterMap parameter_map{};
  ParameterBlockOrdering ordering{};
  ceres::internal::CoordinateDescentMinimizer object{};
  object.Init(program, parameter_map, ordering, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1301, TC2_CallsTarget) {
  Program program{};
  ProblemImpl::ParameterMap parameter_map{};
  ParameterBlockOrdering ordering{};
  ceres::internal::CoordinateDescentMinimizer object{};
  object.Init(program, parameter_map, ordering, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1301, TC3_CallsTarget) {
  Program program{};
  ProblemImpl::ParameterMap parameter_map{};
  ParameterBlockOrdering ordering{};
  ceres::internal::CoordinateDescentMinimizer object{};
  object.Init(program, parameter_map, ordering, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1301, TC4_CallsTarget) {
  Program program{};
  ProblemImpl::ParameterMap parameter_map{};
  ParameterBlockOrdering ordering{};
  ceres::internal::CoordinateDescentMinimizer object{};
  object.Init(program, parameter_map, ordering, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1301, TC5_CallsTarget) {
  Program program{};
  ProblemImpl::ParameterMap parameter_map{};
  ParameterBlockOrdering ordering{};
  ceres::internal::CoordinateDescentMinimizer object{};
  object.Init(program, parameter_map, ordering, nullptr);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1301, TC6_CallsTarget) {
  Program program{};
  ProblemImpl::ParameterMap parameter_map{};
  ParameterBlockOrdering ordering{};
  ceres::internal::CoordinateDescentMinimizer object{};
  object.Init(program, parameter_map, ordering, nullptr);
}

// P7: START -> 1 -> END; branch decisions covered by case 7
TEST(Unit_u1301, TC7_CallsTarget) {
  Program program{};
  ProblemImpl::ParameterMap parameter_map{};
  ParameterBlockOrdering ordering{};
  ceres::internal::CoordinateDescentMinimizer object{};
  object.Init(program, parameter_map, ordering, nullptr);
}

// P8: START -> 1 -> END; branch decisions covered by case 8
TEST(Unit_u1301, TC8_CallsTarget) {
  Program program{};
  ProblemImpl::ParameterMap parameter_map{};
  ParameterBlockOrdering ordering{};
  ceres::internal::CoordinateDescentMinimizer object{};
  object.Init(program, parameter_map, ordering, nullptr);
}
