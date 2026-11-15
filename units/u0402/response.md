**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `index` là số nguyên bất kỳ, từ 0 đến 100. `cost_function` khác `nullptr` (để `CHECK` trong constructor không dừng). `loss_function = nullptr`, `parameter_blocks` rỗng. | `index = 37` (chọn cố định, đại diện cho khoảng trên) |

**C. Nhánh không test**

- Không có nhánh nào cần bỏ qua, vì hàm có 0 điểm rẽ nhánh.
- Không có vòng lặp.
- Các `CHECK` trong constructor không bị làm sai.
- `C2 dự kiến = 0 / 0` (không có nhánh nào). Đường đi duy nhất P1 được chạy qua nên tất cả câu lệnh đều được phủ.

**D. File test**

```cpp
// FILE: u0402_test.cc
#include "gtest/gtest.h"
#include "ceres/residual_block.h"

#include <vector>

namespace ceres {
namespace internal {

namespace {

// CostFunction không có parameter block nào, chỉ dùng để dựng ResidualBlock.
class EmptyCostFunction : public CostFunction {
 public:
  EmptyCostFunction() { set_num_residuals(1); }
  bool Evaluate(double const* const* parameters,
                double* residuals,
                double** jacobians) const override {
    residuals[0] = 0.0;
    return true;
  }
};

}  // namespace

// P1: START -> 1 -> END
TEST(ResidualBlockIndexTest, ReturnsIndex_P1) {
  EmptyCostFunction cost_function;
  std::vector<ParameterBlock*> parameter_blocks;
  const int index = 37;
  ResidualBlock residual_block(
      &cost_function, nullptr, parameter_blocks, index);
  residual_block.index();
}

}  // namespace internal
}  // namespace ceres
```