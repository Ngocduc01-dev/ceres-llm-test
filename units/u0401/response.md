**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `size` của ParameterBlock: 1..5. `index` của ResidualBlock: 0..5. Số residual: 1..5. Hàm không có điều kiện nào ràng buộc đầu vào. Các giá trị này chỉ cần thoả CHECK trong constructor: số block và kích thước block phải khớp với CostFunction. | 1 block có `size = 2`, giá trị `{1.5, -2.0}`, 1 residual, `index = 0`, `loss_function = nullptr` |

**C. Nhánh không test**

- Không có nhánh nào, vì hàm không có điểm rẽ nhánh. Không có vòng lặp nên không cần chọn số lần lặp. CFG khớp với mã nguồn.
- Lưu ý: ngoài 3 `#include` ở mục 3.3, file test thêm `#include "ceres/cost_function.h"`. Cần dòng này vì test định nghĩa lớp con của `CostFunction`, mà `residual_block.h` chỉ khai báo trước lớp này.
- `C2 dự kiến = 0 / 0` (tổng số nhánh là 0, nên coi như đạt 100%; test phủ node 1 và đường START → END).

**D. File test**

```cpp
// FILE: u0401_test.cc
#include <vector>

#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/parameter_block.h"
#include "ceres/residual_block.h"

namespace ceres {
namespace internal {

namespace {

// CostFunction đơn giản: 1 residual, 1 parameter block kích thước 2.
class SimpleCostFunction : public CostFunction {
 public:
  SimpleCostFunction() {
    set_num_residuals(1);
    mutable_parameter_block_sizes()->push_back(2);
  }

  bool Evaluate(double const* const* parameters,
                double* residuals,
                double** jacobians) const override {
    residuals[0] = parameters[0][0] + parameters[0][1];
    if (jacobians != nullptr && jacobians[0] != nullptr) {
      jacobians[0][0] = 1.0;
      jacobians[0][1] = 1.0;
    }
    return true;
  }
};

}  // namespace

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ResidualBlockParameterBlocksTest, TC1_ReturnParameterBlocks) {
  SimpleCostFunction cost_function;
  double x[2] = {1.5, -2.0};
  ParameterBlock parameter_block(x, 2, 0);
  std::vector<ParameterBlock*> parameter_blocks;
  parameter_blocks.push_back(&parameter_block);

  ResidualBlock residual_block(&cost_function, nullptr, parameter_blocks, 0);

  ParameterBlock* const* result = residual_block.parameter_blocks();
  (void)result;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
```