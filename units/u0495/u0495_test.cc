// FILE: u0495_test.cc
#include <random>

#include "ceres/internal/autodiff.h"
#include "gtest/gtest.h"

namespace ceres {
namespace internal {

namespace {

using JetD4 = Jet<double, 4>;

constexpr int kMaxSize = 5;

// Chuẩn bị mảng src (5 phần tử, giá trị sinh từ seed cố định) rồi gọi unit một lần.
void RunTake0thOrderPart(int M) {
  std::mt19937 gen(495);
  std::uniform_real_distribution<double> dist(-10.0, 10.0);

  JetD4 src[kMaxSize];
  double dst[kMaxSize] = {0.0, 0.0, 0.0, 0.0, 0.0};
  for (int i = 0; i < kMaxSize; ++i) {
    src[i] = JetD4(dist(gen));
  }

  Take0thOrderPart<JetD4, double*>(M, src, dst);
}

}  // namespace

// P1: node 1: đúng, node 2: sai (0 lần lặp)
TEST(Take0thOrderPartTest, ZeroIterations) { RunTake0thOrderPart(0); }

// P2: node 1: đúng, node 2: đúng x1 rồi sai (1 lần lặp)
TEST(Take0thOrderPartTest, OneIteration) { RunTake0thOrderPart(1); }

// P3: node 1: đúng, node 2: đúng x2 rồi sai (2 lần lặp)
TEST(Take0thOrderPartTest, TwoIterations) { RunTake0thOrderPart(2); }

// P4: node 1: đúng, node 2: đúng x3 rồi sai (số lần lặp ở giữa)
TEST(Take0thOrderPartTest, ThreeIterations) { RunTake0thOrderPart(3); }

// P5: node 1: đúng, node 2: đúng x4 rồi sai (n-1 lần lặp)
TEST(Take0thOrderPartTest, FourIterations) { RunTake0thOrderPart(4); }

// P6: node 1: đúng, node 2: đúng x5 rồi sai (n lần lặp)
TEST(Take0thOrderPartTest, FiveIterations) { RunTake0thOrderPart(5); }

}  // namespace internal
}  // namespace ceres
