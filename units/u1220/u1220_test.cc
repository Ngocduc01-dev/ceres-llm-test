// FILE: u1220_test.cc
#include "gtest/gtest.h"
#include "ceres/line_search_preprocessor.h"
#include "ceres/evaluator.h"
#include "ceres/preprocessor.h"
#include "ceres/problem_impl.h"
#include "ceres/line_search_preprocessor.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1220, TC1_CallsTarget) {
  ceres::internal::(anonymous)::SetupEvaluator(nullptr);
}
