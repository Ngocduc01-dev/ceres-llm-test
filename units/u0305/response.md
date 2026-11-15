**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `x`, `delta`: mảng 2 phần tử, mỗi phần tử là số thực bất kỳ. `x_plus_delta`: mảng 2 phần tử. Hàm không có điều kiện đường đi nên không bị ràng buộc thêm. | `x = {0.7, -1.3}`, `delta = {0.4, 2.1}`, `x_plus_delta = {0, 0}` |

**C. Nhánh không test**

- Không có. Hàm chỉ có 1 node và 0 điểm rẽ nhánh. CFG khớp với mã nguồn.
- C2 dự kiến = 0 / 0 (không có nhánh nào cần phủ). Test P1 phủ 100% câu lệnh của hàm.

**D. File test**

```cpp
// FILE: u0305_test.cc
#include "gtest/gtest.h"
#include "ceres/gradient_problem.h"
#include "ceres/manifold.h"

namespace ceres {
namespace {

// Hàm mục tiêu đơn giản với 2 tham số, chỉ dùng để dựng GradientProblem.
class SimpleFirstOrderFunction final : public FirstOrderFunction {
 public:
  bool Evaluate(const double* const parameters,
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

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(GradientProblemPlusTest, P1_SingleStatementReturn) {
  GradientProblem problem(new SimpleFirstOrderFunction());

  const double x[2] = {0.7, -1.3};
  const double delta[2] = {0.4, 2.1};
  double x_plus_delta[2] = {0.0, 0.0};

  problem.Plus(x, delta, x_plus_delta);
}

}  // namespace
}  // namespace ceres
```