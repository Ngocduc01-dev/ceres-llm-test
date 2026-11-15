**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 4 → END | node 1: đúng, node 2: sai |
| P2 | START → 1 → 4 → END | node 1: sai |
| P3 | START → 1 → 2 → 3 → END | node 1: đúng, node 2: đúng |

Hàm không có vòng lặp. Đệ quy ở node 4 dừng ngay ở bản đặc biệt hóa với dãy rỗng, nên không có yêu cầu về số lần lặp.

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `jacobians[0]` ≠ nullptr (trỏ tới mảng 4 phần tử); functor trả `true`; `x[i]` ∈ [-5, 5]; `num_residuals` = 1 | `x[i]` sinh bằng `std::mt19937` seed 42; `num_residuals` = 1 |
| TC2 | P2 | `jacobians[0]` = nullptr; `x[i]` ∈ [-5, 5]; `num_residuals` = 1 | `x[i]` sinh bằng `std::mt19937` seed 42; `num_residuals` = 1 |
| TC3 | P3 | `jacobians[0]` ≠ nullptr; functor trả `false`; `x[i]` ∈ [-5, 5]; `num_residuals` = 1 | `x[i]` sinh bằng `std::mt19937` seed 42; `num_residuals` = 1 |

**C. Nhánh không test**

Không có. Cả 4 nhánh đều đi tới được. Node 2 đúng xảy ra khi functor trả `false`, khiến `EvaluateJacobianForParameterBlock` trả `false`.

`C2 dự kiến = 4 / 4` (dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0496_test.cc
#include <random>

#include "ceres/internal/numeric_diff.h"
#include "ceres/numeric_diff_options.h"
#include "gtest/gtest.h"

namespace ceres {
namespace internal {

namespace {

// Functor: residual = sum(x_i^2), một khối tham số kích thước 4, 1 residual.
// Trường succeed quyết định functor trả true hay false.
struct QuadraticCostFunctor {
  explicit QuadraticCostFunctor(bool succeed_in) : succeed(succeed_in) {}
  bool operator()(const double* x, double* residual) const {
    residual[0] = x[0] * x[0] + x[1] * x[1] + x[2] * x[2] + x[3] * x[3];
    return succeed;
  }
  bool succeed;
};

}  // namespace

// Path P1: node 1: đúng, node 2: sai -> node 4 -> END
TEST(EvaluateJacobianForParameterBlocksApplyTest, JacobianRequestedAndFunctorSucceeds) {
  std::mt19937 gen(42);
  std::uniform_real_distribution<double> dist(-5.0, 5.0);
  double x[4];
  for (int i = 0; i < 4; ++i) {
    x[i] = dist(gen);
  }
  double* parameters[1] = {x};
  double residuals_at_eval_point[1] = {
      x[0] * x[0] + x[1] * x[1] + x[2] * x[2] + x[3] * x[3]};
  double jacobian[4] = {0.0, 0.0, 0.0, 0.0};
  double* jacobians[1] = {jacobian};

  QuadraticCostFunctor functor(true);
  NumericDiffOptions options;
  EvaluateJacobianForParameterBlocks<ParameterDims<false, 4>> obj;
  obj.Apply<CENTRAL, 1>(
      &functor, residuals_at_eval_point, options, 1, parameters, jacobians);
}

// Path P2: node 1: sai -> node 4 -> END
TEST(EvaluateJacobianForParameterBlocksApplyTest, JacobianNotRequested) {
  std::mt19937 gen(42);
  std::uniform_real_distribution<double> dist(-5.0, 5.0);
  double x[4];
  for (int i = 0; i < 4; ++i) {
    x[i] = dist(gen);
  }
  double* parameters[1] = {x};
  double residuals_at_eval_point[1] = {
      x[0] * x[0] + x[1] * x[1] + x[2] * x[2] + x[3] * x[3]};
  double* jacobians[1] = {nullptr};

  QuadraticCostFunctor functor(true);
  NumericDiffOptions options;
  EvaluateJacobianForParameterBlocks<ParameterDims<false, 4>> obj;
  obj.Apply<CENTRAL, 1>(
      &functor, residuals_at_eval_point, options, 1, parameters, jacobians);
}

// Path P3: node 1: đúng, node 2: đúng -> node 3 -> END
TEST(EvaluateJacobianForParameterBlocksApplyTest, JacobianRequestedAndFunctorFails) {
  std::mt19937 gen(42);
  std::uniform_real_distribution<double> dist(-5.0, 5.0);
  double x[4];
  for (int i = 0; i < 4; ++i) {
    x[i] = dist(gen);
  }
  double* parameters[1] = {x};
  double residuals_at_eval_point[1] = {
      x[0] * x[0] + x[1] * x[1] + x[2] * x[2] + x[3] * x[3]};
  double jacobian[4] = {0.0, 0.0, 0.0, 0.0};
  double* jacobians[1] = {jacobian};

  QuadraticCostFunctor functor(false);
  NumericDiffOptions options;
  EvaluateJacobianForParameterBlocks<ParameterDims<false, 4>> obj;
  obj.Apply<CENTRAL, 1>(
      &functor, residuals_at_eval_point, options, 1, parameters, jacobians);
}

}  // namespace internal
}  // namespace ceres
```