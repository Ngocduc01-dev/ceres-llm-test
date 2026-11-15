**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có điểm rẽ nhánh nên không có nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Hàm không có tham số. Cần một object `DoglegStrategy` hợp lệ, với `options.linear_solver` khác `nullptr` (constructor có thể dùng `CHECK` kiểm tra con trỏ này). | `options.linear_solver` trỏ tới một `LinearSolver` giả (stub); các trường còn lại để mặc định |

**C. Nhánh không test**

Không có. Hàm có 0 điểm rẽ nhánh nên không có nhánh nào bị bỏ sót và không có vòng lặp.
`C2 dự kiến = 0 / 0` (không có nhánh nào, coi như đạt 100%; chưa chạy thật).

Ghi chú: CFG khớp với mã nguồn (hàm chỉ có một lệnh `return`). Stub `LinearSolver` chỉ ghi đè `Solve`, giả định đây là hàm thuần ảo duy nhất của lớp cơ sở. Nếu bản 2.2.0 có thêm hàm thuần ảo khác thì phải bổ sung vào stub.

**D. File test**

```cpp
// FILE: u0285_test.cc
#include "gtest/gtest.h"
#include "ceres/dogleg_strategy.h"

namespace ceres {
namespace internal {

namespace {

// LinearSolver giả, chỉ dùng để constructor của DoglegStrategy có con trỏ hợp lệ.
class StubLinearSolver : public LinearSolver {
 public:
  Summary Solve(LinearOperator* A,
                const double* b,
                const PerSolveOptions& per_solve_options,
                double* x) override {
    return Summary();
  }
};

}  // namespace

// P1: START -> END (không có điểm rẽ nhánh)
TEST(DoglegStrategyGaussNewtonStep, P1_NoBranch) {
  StubLinearSolver solver;
  TrustRegionStrategy::Options options;
  options.linear_solver = &solver;

  DoglegStrategy strategy(options);
  Vector step = strategy.gauss_newton_step();
  (void)step;  // không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
```