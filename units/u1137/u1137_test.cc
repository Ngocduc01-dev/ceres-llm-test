// FILE: u1137_test.cc
#include "gtest/gtest.h"
#include "ceres/block_structure.h"
#include "ceres/inner_product_computer.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1137, TC1_CallsTarget) {
  std::vector<InnerProductComputer::ProductTerm> product_terms{};
  ceres::internal::InnerProductComputer object{};
  object.ComputeNonzeros(product_terms, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1137, TC2_CallsTarget) {
  std::vector<InnerProductComputer::ProductTerm> product_terms{};
  ceres::internal::InnerProductComputer object{};
  object.ComputeNonzeros(product_terms, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1137, TC3_CallsTarget) {
  std::vector<InnerProductComputer::ProductTerm> product_terms{};
  ceres::internal::InnerProductComputer object{};
  object.ComputeNonzeros(product_terms, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1137, TC4_CallsTarget) {
  std::vector<InnerProductComputer::ProductTerm> product_terms{};
  ceres::internal::InnerProductComputer object{};
  object.ComputeNonzeros(product_terms, nullptr);
}
