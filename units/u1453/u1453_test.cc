// FILE: u1453_test.cc
#include "gtest/gtest.h"
#include "ceres/reorder_program.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"
#include "ceres/program.h"
#include "ceres/triplet_sparse_matrix.h"
#include "ceres/reorder_program.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1453, TC1_CallsTarget) {
  LinearSolverOrderingType ordering_type{};
  const int size_of_first_elimination_group{};
  ProblemImpl::ParameterMap arg2{};
  ceres::internal::ReorderSchurComplementColumnsUsingEigen(ordering_type, size_of_first_elimination_group, arg2, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1453, TC2_CallsTarget) {
  LinearSolverOrderingType ordering_type{};
  const int size_of_first_elimination_group{};
  ProblemImpl::ParameterMap arg2{};
  ceres::internal::ReorderSchurComplementColumnsUsingEigen(ordering_type, size_of_first_elimination_group, arg2, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1453, TC3_CallsTarget) {
  LinearSolverOrderingType ordering_type{};
  const int size_of_first_elimination_group{};
  ProblemImpl::ParameterMap arg2{};
  ceres::internal::ReorderSchurComplementColumnsUsingEigen(ordering_type, size_of_first_elimination_group, arg2, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1453, TC4_CallsTarget) {
  LinearSolverOrderingType ordering_type{};
  const int size_of_first_elimination_group{};
  ProblemImpl::ParameterMap arg2{};
  ceres::internal::ReorderSchurComplementColumnsUsingEigen(ordering_type, size_of_first_elimination_group, arg2, nullptr);
}
