**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

Hàm có 0 điểm rẽ nhánh và không có vòng lặp, nên một test path duy nhất là đủ. CFG khớp với mã nguồn (dòng 113–115).

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `parameters`: 1 khối tham số, 1 phần tử, `x` ∈ [-10, 10]. `residuals`: mảng 1 phần tử. | `x = 3.0`, `residuals[0] = 0.0` |

**C. Nhánh không test**

Không có. Tổng số nhánh bằng 0, và `Evaluate` được gọi với `jacobians = nullptr` nên không có nhánh nào bị bỏ.

`C2 dự kiến = 0 / 0` (không có nhánh nào cần phủ, nên coi là 100%; dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0020_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/dynamic_cost_function_to_functor.h"

namespace {

// CostFunction đơn giản: 1 khối tham số kích thước 1, 1 residual.
class SimpleCostFunction : public ceres::CostFunction {
 public:
  SimpleCostFunction() {
    set_num_residuals(1);
    mutable_parameter_block_sizes()->push_back(1);
  }

  bool Evaluate(double const* const* parameters,
                double* residuals,
                double** jacobians) const override {
    residuals[0] = parameters[0][0];
    if (jacobians != nullptr && jacobians[0] != nullptr) {
      jacobians[0][0] = 1.0;
    }
    return true;
  }
};

}  // namespace

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(DynamicCostFunctionToFunctorTest, TC1_P1_CallEvaluate) {
  // Functor sở hữu cost function (unique_ptr bên trong).
  ceres::DynamicCostFunctionToFunctor functor(new SimpleCostFunction());

  double x = 3.0;
  const double* parameter_blocks[1] = {&x};
  double residuals[1] = {0.0};

  functor(parameter_blocks, residuals);
}
```