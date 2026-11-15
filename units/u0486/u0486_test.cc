// FILE: u0486_test.cc
#include <random>
#include <vector>

#include "gtest/gtest.h"
#include "ceres/iteration_callback.h"
#include "ceres/solver_utils.h"

namespace ceres {
namespace internal {

namespace {

// Kiểu summary tối giản, có đúng các thành viên mà SetSummaryFinalCost dùng.
struct FakeSummary {
  double initial_cost = 0.0;
  double final_cost = 0.0;
  std::vector<IterationSummary> iterations;
};

// Tạo summary với n iteration, giá trị cost sinh ngẫu nhiên trong [0, 100]
// với seed cố định để kết quả lặp lại được.
FakeSummary MakeSummary(int n) {
  std::mt19937 gen(486);
  std::uniform_real_distribution<double> dist(0.0, 100.0);
  FakeSummary summary;
  summary.initial_cost = dist(gen);
  summary.iterations.resize(n);
  for (int i = 0; i < n; ++i) {
    summary.iterations[i].cost = dist(gen);
  }
  return summary;
}

}  // namespace

// P1: START -> 1 -> 2 -> END ; node 2: sai (0 lần lặp)
TEST(SetSummaryFinalCostTest, TC1_ZeroIterations) {
  FakeSummary summary = MakeSummary(0);
  SetSummaryFinalCost(&summary);
}

// P2: START -> 1 -> (2 -> 3 -> 4) x1 -> 2 -> END ; node 2: đúng x1, rồi sai
TEST(SetSummaryFinalCostTest, TC2_OneIteration) {
  FakeSummary summary = MakeSummary(1);
  SetSummaryFinalCost(&summary);
}

// P3: START -> 1 -> (2 -> 3 -> 4) x2 -> 2 -> END ; node 2: đúng x2, rồi sai
TEST(SetSummaryFinalCostTest, TC3_TwoIterations) {
  FakeSummary summary = MakeSummary(2);
  SetSummaryFinalCost(&summary);
}

// P4: START -> 1 -> (2 -> 3 -> 4) x3 -> 2 -> END ; node 2: đúng x3, rồi sai
TEST(SetSummaryFinalCostTest, TC4_ThreeIterations) {
  FakeSummary summary = MakeSummary(3);
  SetSummaryFinalCost(&summary);
}

// P5: START -> 1 -> (2 -> 3 -> 4) x4 -> 2 -> END ; node 2: đúng x4, rồi sai
TEST(SetSummaryFinalCostTest, TC5_FourIterations) {
  FakeSummary summary = MakeSummary(4);
  SetSummaryFinalCost(&summary);
}

// P6: START -> 1 -> (2 -> 3 -> 4) x5 -> 2 -> END ; node 2: đúng x5, rồi sai
TEST(SetSummaryFinalCostTest, TC6_FiveIterations) {
  FakeSummary summary = MakeSummary(5);
  SetSummaryFinalCost(&summary);
}

}  // namespace internal
}  // namespace ceres
