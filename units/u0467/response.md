**A. Test paths**

Unit không có điểm rẽ nhánh nào. `std::max` và `std::min` là lời gọi hàm, không tính là rẽ nhánh. Vì vậy chỉ có một test path.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → END | node 1: `CHECK_GT` đúng (không tính nhánh). Không có điểm rẽ nhánh nào khác. |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `step_quality` > 0.0 (để `CHECK_GT` đúng). Lấy trong (0, 1]. | `step_quality = 0.7` (cố định, không dùng số ngẫu nhiên) |

Các tham số dựng object (để constructor không dừng bởi `CHECK`): `linear_solver != nullptr`, `min_lm_diagonal > 0`, `min_lm_diagonal <= max_lm_diagonal`, `max_radius > 0`, `initial_radius = 1e4`, `max_radius = 1e8`.

**C. Nhánh không test**

- Nhánh `CHECK_GT(step_quality, 0.0)` sai (node 1 → DỪNG): không test (làm chương trình dừng).
- Mã nguồn khớp với CFG, không có điểm khác biệt.
- `C2 dự kiến = 0 / 0` (tổng số nhánh = 0 nên C2 không xác định, coi như phủ đủ). Test duy nhất đi hết node 1 → 2 → END.

**D. File test**

```cpp
// FILE: u0467_test.cc
#include "gtest/gtest.h"
#include "ceres/levenberg_marquardt_strategy.h"

#include <memory>

namespace ceres {
namespace internal {

// TC1 - P1: START -> 1 (CHECK_GT đúng) -> 2 -> END
TEST(LevenbergMarquardtStrategyStepAcceptedTest, P1_PositiveStepQuality) {
  LinearSolver::Options linear_solver_options;
  linear_solver_options.type = DENSE_QR;
  std::unique_ptr<LinearSolver> linear_solver(
      LinearSolver::Create(linear_solver_options));

  TrustRegionStrategy::Options options;
  options.linear_solver = linear_solver.get();
  options.initial_radius = 1e4;
  options.max_radius = 1e8;
  options.min_lm_diagonal = 1e-6;
  options.max_lm_diagonal = 1e32;

  LevenbergMarquardtStrategy strategy(options);
  strategy.StepAccepted(0.7);
}

}  // namespace internal
}  // namespace ceres
```