// FILE: u1137_test.cc
#include "gtest/gtest.h"
#include "ceres/block_structure.h"
#include "ceres/inner_product_computer.h"

// P1: START -> 1 -> END
TEST(ComputeNonzerosTest, TC1_CallsTarget) {
  InnerProductComputer object{};
  std::vector<InnerProductComputer::ProductTerm> & product_terms a0{};
  int a1[5] = {};
  object.ComputeNonzeros(a0, a1);
}

// P2: START -> 1 -> END
TEST(ComputeNonzerosTest, TC2_CallsTarget) {
  InnerProductComputer object{};
  std::vector<InnerProductComputer::ProductTerm> & product_terms a0{};
  int a1[5] = {};
  object.ComputeNonzeros(a0, a1);
}

// P3: START -> 1 -> END
TEST(ComputeNonzerosTest, TC3_CallsTarget) {
  InnerProductComputer object{};
  std::vector<InnerProductComputer::ProductTerm> & product_terms a0{};
  int a1[5] = {};
  object.ComputeNonzeros(a0, a1);
}

