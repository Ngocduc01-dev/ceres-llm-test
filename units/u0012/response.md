**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh (0 điểm rẽ nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Hàm không có tham số. Object `CostFunction` mới tạo, `parameter_block_sizes_` rỗng (không có điều kiện ràng buộc) | Object con `DummyCostFunction` tạo bằng constructor mặc định, không gọi `mutable_parameter_block_sizes()` |

Ghi chú: CFG khớp với mã nguồn (một câu lệnh `return`).

**C. Nhánh không test**

Không có nhánh nào (hàm không có điểm rẽ nhánh, không có `CHECK`, không có vòng lặp).

`C2 dự kiến = 0 / 0` (không có nhánh; toàn bộ câu lệnh node 1 được chạy bởi TC1, tức hàm được phủ hoàn toàn bằng 1 test).

**D. File test**

```cpp
// FILE: u0012_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"

namespace ceres {
namespace {

// Lớp con để tạo được object, vì CostFunction có hàm thuần ảo Evaluate.
class DummyCostFunction : public CostFunction {
 public:
  bool Evaluate(double const* const* parameters,
                double* residuals,
                double** jacobians) const override {
    return true;
  }
};

// TC1 - Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(CostFunctionParameterBlockSizesTest, ReturnsParameterBlockSizes) {
  DummyCostFunction cost_function;
  const std::vector<int32_t>& sizes = cost_function.parameter_block_sizes();
  (void)sizes;  // Không kiểm tra kết quả trả về.
}

}  // namespace
}  // namespace ceres
```