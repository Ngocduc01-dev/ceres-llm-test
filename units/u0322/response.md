**A. Test paths**

Hàm không có điểm rẽ nhánh (0 điểm, 0 nhánh), nên chỉ có một đường đi.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh nào (đường thẳng) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `step_quality`: bất kỳ double (tham số không được dùng), chọn trong [0, 1]. `initial_radius` > 0 (để `radius_` hợp lệ), chọn trong [1, 1e4]. | `step_quality` = 0.37; `initial_radius` = 100.0 |

**C. Nhánh không test**

- Không có nhánh nào bị bỏ. Các `CHECK` trong constructor (`linear_solver != nullptr`, `min_lm_diagonal > 0`, ...) không bị làm sai: options được đặt hợp lệ và `linear_solver` trỏ tới một solver giả.
- `C2 dự kiến = 0 / 0` (hàm không có nhánh, nên C2 coi như đạt 100%). Test vẫn chạy toàn bộ node 1.

**D. File test**

```cpp
// FILE: u0322_test.cc
#include "gtest/gtest.h"
#include "ceres/levenberg_marquardt_strategy.h"

namespace ceres {
namespace internal {

namespace {

// Linear solver giả chỉ để thoả CHECK(linear_solver != nullptr) trong constructor.
// Hàm StepRejected không dùng tới solver này.
class FakeLinearSolver : public LinearSolver {
 public:
  Summary Solve(LinearOperator* /*A*/,
                const double* /*b*/,
                const PerSolveOptions& /*per_solve_options*/,
                double* /*x*/) override {
    return Summary();
  }
};

}  // namespace

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(LevenbergMarquardtStrategyStepRejectedTest, TC1_P1_StraightLine) {
  FakeLinearSolver linear_solver;

  TrustRegionStrategy::Options options;
  options.linear_solver = &linear_solver;
  options.initial_radius = 100.0;
  options.max_radius = 1e16;
  options.min_lm_diagonal = 1e-6;
  options.max_lm_diagonal = 1e32;

  LevenbergMarquardtStrategy strategy(options);
  strategy.StepRejected(0.37);
}

}  // namespace internal
}  // namespace ceres
```