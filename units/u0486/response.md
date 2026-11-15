**A. Test paths**

Có 1 điểm rẽ nhánh (node 2, vòng `for`), nên tổng số nhánh là 2. Mỗi path chạy vòng lặp k lần (k = `iterations.size()`).

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → END | node 2: sai (0 lần lặp) |
| P2 | START → 1 → (2 → 3 → 4) ×1 → 2 → END | node 2: đúng ×1, rồi sai |
| P3 | START → 1 → (2 → 3 → 4) ×2 → 2 → END | node 2: đúng ×2, rồi sai |
| P4 | START → 1 → (2 → 3 → 4) ×3 → 2 → END | node 2: đúng ×3, rồi sai (số lần ở giữa) |
| P5 | START → 1 → (2 → 3 → 4) ×4 → 2 → END | node 2: đúng ×4, rồi sai (n−1) |
| P6 | START → 1 → (2 → 3 → 4) ×5 → 2 → END | node 2: đúng ×5, rồi sai (n) |

**B. Bộ test case**

Giới hạn n = 5 do yêu cầu mảng tối đa 5 phần tử. Giá trị `cost` và `initial_cost` nằm trong khoảng [0, 100], sinh bằng `std::mt19937` với seed cố định 486.

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `iterations.size()` = 0; `initial_cost` ∈ [0,100] | size = 0; `initial_cost` sinh từ seed 486 |
| TC2 | P2 | size = 1; cost ∈ [0,100] | size = 1; cost sinh từ seed 486 |
| TC3 | P3 | size = 2; cost ∈ [0,100] | size = 2; cost sinh từ seed 486 |
| TC4 | P4 | size = 3; cost ∈ [0,100] | size = 3; cost sinh từ seed 486 |
| TC5 | P5 | size = 4; cost ∈ [0,100] | size = 4; cost sinh từ seed 486 |
| TC6 | P6 | size = 5; cost ∈ [0,100] | size = 5; cost sinh từ seed 486 |

**C. Nhánh không test**

- Không có nhánh nào không thể đi tới và không có `CHECK`.
- Lặp n+1 lần là không làm được, vì vòng lặp luôn chạy đúng `iterations.size()` lần.
- Do `SetSummaryFinalCost` là template, file test dùng kiểu `FakeSummary` có đúng 3 thành viên mà hàm dùng (`initial_cost`, `final_cost`, `iterations`). Điều này không làm thay đổi CFG.
- `C2 dự kiến = 2 / 2` (dự kiến, chưa chạy thật).

**D. File test**

```cpp
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
```