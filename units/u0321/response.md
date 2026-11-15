**A. Test paths**

Hàm có 0 điểm rẽ nhánh, nên chỉ có một đường đi duy nhất. Mã nguồn khớp với CFG: dòng 66 là `= default`, không có lệnh nào.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có nhánh nào (0 điểm rẽ nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `options.linear_solver` phải khác `nullptr` (constructor có `CHECK`). Các trường còn lại dùng giá trị mặc định hợp lệ của `TrustRegionStrategy::Options`. `LinearSolver::Options::type` thuộc tập kiểu solver hợp lệ. | `linear_solver` = solver `DENSE_QR`, các trường khác mặc định. Không dùng số ngẫu nhiên nên không cần seed. |

**C. Nhánh không test**

- Không có nhánh nào cần loại, vì hàm không có điểm rẽ nhánh.
- Các `CHECK` trong constructor không được tính vào tổng số nhánh và không bị làm sai.
- `C2 dự kiến = 0 / 0` (không có nhánh nào, coi như đạt 100%). Đây là giá trị dự kiến, chưa chạy thật.

**D. File test**

```cpp
// FILE: u0321_test.cc
#include "gtest/gtest.h"
#include "ceres/levenberg_marquardt_strategy.h"

namespace ceres {
namespace internal {

// TC1 - Path P1: START -> END (destructor mặc định, không có nhánh)
TEST(LevenbergMarquardtStrategyDestructorTest, P1_StartToEnd) {
  LinearSolver::Options linear_solver_options;
  linear_solver_options.type = DENSE_QR;
  std::unique_ptr<LinearSolver> linear_solver(
      LinearSolver::Create(linear_solver_options));

  TrustRegionStrategy::Options options;
  options.linear_solver = linear_solver.get();

  std::unique_ptr<LevenbergMarquardtStrategy> strategy(
      new LevenbergMarquardtStrategy(options));
  // Gọi destructor đúng một lần.
  strategy.reset();
}

}  // namespace internal
}  // namespace ceres
```