**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh (đường đi duy nhất) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `x` (tham số) ∈ [1, 5]; `residuals[0]` ∈ [1, 5]; `num_residuals` = 1; `num_parameter_blocks` = 1; `parameter_block_sizes[0]` = 1; `jacobians` = `nullptr` (đại diện cho trường hợp không cần jacobian); callback trả về `true`/`false` tuỳ ý | `x` = 3.0; `residuals[0]` = 2.0; `user_data` = địa chỉ biến đếm; `jacobians` = `nullptr` |

**C. Nhánh không test**

- Không có. Hàm không có điểm rẽ nhánh, không có vòng lặp, không có `CHECK`.
- Ghi chú: class `CallbackCostFunction` được định nghĩa trong `c_api.cc`, nên file test cần liên kết với định nghĩa này. Tôi giữ đúng `#include` ở mục 3.3.
- `C2 dự kiến = 0 / 0 (không có nhánh nào, coi là 100%; đường đi duy nhất P1 được chạy qua)`

**D. File test**

```cpp
// FILE: u0244_test.cc
#include "gtest/gtest.h"

namespace {

// Hàm callback giả: ghi nhận số lần được gọi qua user_data, không kiểm tra kết quả.
int FakeCostFunction(void* user_data,
                     double** parameters,
                     double* residuals,
                     double** jacobians) {
  int* counter = static_cast<int*>(user_data);
  ++(*counter);
  residuals[0] = parameters[0][0];
  return 1;
}

}  // namespace

// P1: START -> 1 -> END
TEST(CallbackCostFunctionEvaluate, TC1_SingleStatement) {
  int call_count = 0;
  int parameter_block_sizes[1] = {1};
  ceres::CallbackCostFunction cost_function(
      FakeCostFunction, &call_count, 1, 1, parameter_block_sizes);

  double x = 3.0;
  const double* const parameters[1] = {&x};
  double residuals[1] = {2.0};

  cost_function.Evaluate(parameters, residuals, nullptr);
}
```