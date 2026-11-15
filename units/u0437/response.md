**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → END | node 1: đúng (`jacobians == nullptr`) |
| P2 | START → 1 → 3 → END | node 1: sai (`jacobians != nullptr`) |

Hàm không có vòng lặp. CFG khớp với mã nguồn.

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `jacobians = nullptr`; `parameters` gồm 2 khối, mỗi khối 2 số thực trong [-5, 5]; `residuals` có 1 phần tử | `x = {1.3, -0.7}`, `y = {2.1, 0.4}`, `jacobians = nullptr` |
| TC2 | P2 | `jacobians` khác `nullptr`, gồm 2 con trỏ, mỗi con trỏ trỏ tới mảng 2 phần tử (1 residual × 2 tham số); `parameters` như TC1 | `x = {1.3, -0.7}`, `y = {2.1, 0.4}`, `jacobians = {j0, j1}` |

**C. Nhánh không test**

Không có nhánh nào bị bỏ qua. Hàm không có `CHECK` trực tiếp và không có nhánh không thể đi tới.

`C2 dự kiến = 2 / 2`

**D. File test**

```cpp
// FILE: u0437_test.cc
#include "gtest/gtest.h"
#include "ceres/autodiff_cost_function.h"
#include "ceres/sized_cost_function.h"

namespace {

struct BinaryScalarCost {
  template <typename T>
  bool operator()(const T* x, const T* y, T* residual) const {
    residual[0] = x[0] * y[0] + x[1] * y[1];
    return true;
  }
};

// P1: node 1: đúng (jacobians == nullptr) -> node 2 -> END
TEST(AutoDiffCostFunctionEvaluateTest, NullJacobians) {
  BinaryScalarCost functor;
  ceres::AutoDiffCostFunction<BinaryScalarCost, 1, 2, 2> cost_function(
      &functor, ceres::DO_NOT_TAKE_OWNERSHIP);

  double x[2] = {1.3, -0.7};
  double y[2] = {2.1, 0.4};
  const double* parameters[2] = {x, y};
  double residuals[1] = {0.0};

  cost_function.Evaluate(parameters, residuals, nullptr);
}

// P2: node 1: sai (jacobians != nullptr) -> node 3 -> END
TEST(AutoDiffCostFunctionEvaluateTest, NonNullJacobians) {
  BinaryScalarCost functor;
  ceres::AutoDiffCostFunction<BinaryScalarCost, 1, 2, 2> cost_function(
      &functor, ceres::DO_NOT_TAKE_OWNERSHIP);

  double x[2] = {1.3, -0.7};
  double y[2] = {2.1, 0.4};
  const double* parameters[2] = {x, y};
  double residuals[1] = {0.0};
  double j0[2] = {0.0, 0.0};
  double j1[2] = {0.0, 0.0};
  double* jacobians[2] = {j0, j1};

  cost_function.Evaluate(parameters, residuals, jacobians);
}

}  // namespace
```