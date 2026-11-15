// FILE: u0496_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/numeric_diff.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0496, PathP1) {
  const NumericDiffOptions& arg_2{}
  const CostFunctor* arg_0 = nullptr;
  const double* arg_1 = nullptr;
  const NumericDiffOptions& arg_2{};
  int arg_3 = 1;
  double** arg_4 = nullptr;
  double** arg_5 = nullptr;
  ceres::EvaluateJacobianForParameterBlocks<ParameterDims<false, 4>>::Apply<CENTRAL, 1, QuadraticCostFunctor> target(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5);
  target.Apply(nullptr, nullptr, arg_2, 1, nullptr, nullptr);
}

// Path P2: START -> 1 -> END.
TEST(Unit_u0496, PathP2) {
  const NumericDiffOptions& arg_2{}
  const CostFunctor* arg_0 = nullptr;
  const double* arg_1 = nullptr;
  const NumericDiffOptions& arg_2{};
  int arg_3 = 1;
  double** arg_4 = nullptr;
  double** arg_5 = nullptr;
  ceres::EvaluateJacobianForParameterBlocks<ParameterDims<false, 4>>::Apply<CENTRAL, 1, QuadraticCostFunctor> target(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5);
  target.Apply(nullptr, nullptr, arg_2, 1, nullptr, nullptr);
}

// Path P3: START -> 1 -> END.
TEST(Unit_u0496, PathP3) {
  const NumericDiffOptions& arg_2{}
  const CostFunctor* arg_0 = nullptr;
  const double* arg_1 = nullptr;
  const NumericDiffOptions& arg_2{};
  int arg_3 = 1;
  double** arg_4 = nullptr;
  double** arg_5 = nullptr;
  ceres::EvaluateJacobianForParameterBlocks<ParameterDims<false, 4>>::Apply<CENTRAL, 1, QuadraticCostFunctor> target(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5);
  target.Apply(nullptr, nullptr, arg_2, 1, nullptr, nullptr);
}

// Path P4: START -> 1 -> END.
TEST(Unit_u0496, PathP4) {
  const NumericDiffOptions& arg_2{}
  const CostFunctor* arg_0 = nullptr;
  const double* arg_1 = nullptr;
  const NumericDiffOptions& arg_2{};
  int arg_3 = 1;
  double** arg_4 = nullptr;
  double** arg_5 = nullptr;
  ceres::EvaluateJacobianForParameterBlocks<ParameterDims<false, 4>>::Apply<CENTRAL, 1, QuadraticCostFunctor> target(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5);
  target.Apply(nullptr, nullptr, arg_2, 1, nullptr, nullptr);
}
