// FILE: u0023_test.cc
#include <array>
#include <random>
#include <utility>

#include "gtest/gtest.h"
#include "ceres/internal/autodiff.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(Make1stOrderPerturbationsApply, P1_TwoBlocksOfSizeTwo) {
  std::mt19937 gen(42);
  std::uniform_real_distribution<double> dist(-10.0, 10.0);

  double block0[2] = {dist(gen), dist(gen)};
  double block1[2] = {dist(gen), dist(gen)};
  const double* parameters[2] = {block0, block1};

  Jet<double, 4> x[4];

  Make1stOrderPerturbations<std::integer_sequence<int, 2, 2>> obj;
  obj.Apply(parameters, x);
}

}  // namespace internal
}  // namespace ceres
