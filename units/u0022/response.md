**A. Test paths**

Unit không có điểm rẽ nhánh nào, nên chỉ có một đường đi.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh (node 1: `return function_.get()`) |

CFG khớp với mã nguồn dòng 110. Không có vòng lặp và không có `CHECK`.

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `NumParameters()` của hàm mục tiêu: số nguyên từ 1 đến 5 | 2 (hàm `f(x) = x0² + x1²`, đối tượng được cấp phát bằng `new`, `GradientProblem` sở hữu) |

**C. Nhánh không test**

Không có nhánh nào bị bỏ qua, vì unit không có điểm rẽ nhánh.

`C2 dự kiến = 0 / 0` (không có nhánh nào để phủ; đường đi duy nhất P1 được chạy qua, độ phủ câu lệnh là 100%; dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0022_test.cc
#include "gtest/gtest.h"
#include "ceres/first_order_function.h"
#include "ceres/gradient_problem.h"

namespace {

// Hàm mục tiêu đơn giản: f(x) = x0^2 + x1^2, gồm 2 tham số.
class SimpleQuadraticFunction : public ceres::FirstOrderFunction {
 public:
  bool Evaluate(const double* parameters,
                double* cost,
                double* gradient) const override {
    cost[0] = parameters[0] * parameters[0] + parameters[1] * parameters[1];
    if (gradient != nullptr) {
      gradient[0] = 2.0 * parameters[0];
      gradient[1] = 2.0 * parameters[1];
    }
    return true;
  }

  int NumParameters() const override { return 2; }
};

}  // namespace

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(GradientProblemMutableFunctionTest, P1_ReturnFunctionPointer) {
  ceres::GradientProblem problem(new SimpleQuadraticFunction());
  ceres::FirstOrderFunction* function = problem.mutable_function();
  (void)function;  // Không kiểm tra kết quả trả về.
}
```