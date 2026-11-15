**A. Test paths**

Hàm không có điểm rẽ nhánh (0 điểm, 0 nhánh), nên chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào. Node 1 chạy tuần tự: `return manifold_->TangentSize()`. |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Số tham số `n` của hàm mục tiêu: 1 đến 5 (dùng constructor 1 tham số, manifold mặc định là Euclidean) | `n = 3` (cố định, không dùng số ngẫu nhiên) |

**C. Nhánh không test**

Không có. Hàm không có vòng lặp và không có `CHECK`.

`C2 dự kiến = 0 / 0` (không có nhánh nào, coi như đạt 100%, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0304_test.cc
#include "gtest/gtest.h"
#include "ceres/gradient_problem.h"
#include "ceres/manifold.h"

namespace ceres {
namespace {

// Hàm mục tiêu đơn giản: f(x) = sum(x_i^2), kích thước cố định 3.
class SquaredSumFunction final : public FirstOrderFunction {
 public:
  bool Evaluate(const double* parameters,
                double* cost,
                double* gradient) const override {
    double sum = 0.0;
    for (int i = 0; i < 3; ++i) {
      sum += parameters[i] * parameters[i];
      if (gradient != nullptr) {
        gradient[i] = 2.0 * parameters[i];
      }
    }
    cost[0] = sum;
    return true;
  }

  int NumParameters() const override { return 3; }
};

// P1: START -> 1 -> END (hàm không có điểm rẽ nhánh)
TEST(GradientProblemNumTangentParameters, P1_ReturnTangentSize) {
  GradientProblem problem(new SquaredSumFunction());
  int tangent_size = problem.NumTangentParameters();
  (void)tangent_size;  // Không kiểm tra kết quả trả về
}

}  // namespace
}  // namespace ceres
```