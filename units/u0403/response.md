**A. Test paths**

Hàm có 0 điểm rẽ nhánh, nên chỉ có một đường đi.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `index` là số nguyên bất kỳ, từ INT_MIN đến INT_MAX. Chọn trong khoảng 0 đến 4. | `index = 3` (cố định, không dùng sinh ngẫu nhiên) |

**C. Nhánh không test**

Không có. Hàm không có `CHECK` và không có nhánh không thể đi tới.

`C2 dự kiến = 0 / 0` (không có nhánh nào, nên coi là 100%; chưa chạy thật).

**D. File test**

```cpp
// FILE: u0403_test.cc
#include "gtest/gtest.h"
#include "ceres/residual_block.h"

#include <vector>

namespace ceres {
namespace internal {

namespace {

// CostFunction đơn giản: 0 parameter block, 1 residual.
class DummyCostFunction : public CostFunction {
 public:
  DummyCostFunction() { set_num_residuals(1); }
  bool Evaluate(double const* const* parameters,
                double* residuals,
                double** jacobians) const override {
    residuals[0] = 0.0;
    return true;
  }
};

}  // namespace

// Path P1: START -> 1 -> END
TEST(ResidualBlockSetIndexTest, TC1_P1_SetIndex) {
  DummyCostFunction cost_function;
  std::vector<ParameterBlock*> parameter_blocks;
  ResidualBlock residual_block(&cost_function, nullptr, parameter_blocks, 0);

  residual_block.set_index(3);
}

}  // namespace internal
}  // namespace ceres
```