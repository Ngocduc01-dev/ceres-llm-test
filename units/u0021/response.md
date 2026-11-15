**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Hàm không có tham số. Object `GradientProblem` được tạo từ một `FirstOrderFunction` hợp lệ (không null) có `NumParameters()` = 1 | `function` = `new SimpleFunction` (1 tham số) |

**C. Nhánh không test**

Không có. CFG có 0 điểm rẽ nhánh, nên không có nhánh nào cần test và không có nhánh `CHECK`. CFG khớp với mã nguồn.

`C2 dự kiến = 0 / 0` (không có nhánh nào, nên P1 đi qua toàn bộ hàm và coi như đạt đủ độ phủ).

**D. File test**

```cpp
// FILE: u0021_test.cc
#include "gtest/gtest.h"
#include "ceres/first_order_function.h"
#include "ceres/gradient_problem.h"

namespace ceres {
namespace {

// Hàm một tham số đơn giản, dùng để tạo GradientProblem.
class SimpleFunction final : public FirstOrderFunction {
 public:
  bool Evaluate(const double* parameters,
                double* cost,
                double* gradient) const override {
    cost[0] = parameters[0] * parameters[0];
    if (gradient != nullptr) {
      gradient[0] = 2.0 * parameters[0];
    }
    return true;
  }

  int NumParameters() const override { return 1; }
};

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(GradientProblemFunctionTest, P1_ReturnFunctionPointer) {
  GradientProblem problem(new SimpleFunction());
  const FirstOrderFunction* f = problem.function();
  (void)f;  // Không kiểm tra kết quả trả về.
}

}  // namespace
}  // namespace ceres
```