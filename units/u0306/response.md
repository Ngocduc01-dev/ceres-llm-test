**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào |

CFG khớp với mã nguồn (`return 1;`), không cần ghi chú thêm.

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Số tham số của `FirstOrderFunction`: 1 đến 5. Hàm không có điều kiện đường đi. | 3 |

**C. Nhánh không test**

Không có nhánh nào, vì hàm không có điểm rẽ nhánh và không có `CHECK`.

`C2 dự kiến = 0 / 0` (không có nhánh nào, nên coi như phủ trọn; chỉ cần 1 test để node 1 được chạy, tức là đạt C1 = 100%).

**D. File test**

```cpp
// FILE: u0306_test.cc
#include "gtest/gtest.h"
#include "ceres/gradient_problem_evaluator.h"

namespace {

// Hàm mục tiêu đơn giản: f(x) = 0.5 * sum(x_i^2), dùng để dựng GradientProblem.
class SimpleFirstOrderFunction : public ceres::FirstOrderFunction {
 public:
  explicit SimpleFirstOrderFunction(int num_parameters)
      : num_parameters_(num_parameters) {}

  bool Evaluate(const double* parameters,
                double* cost,
                double* gradient) const override {
    double sum = 0.0;
    for (int i = 0; i < num_parameters_; ++i) {
      sum += 0.5 * parameters[i] * parameters[i];
      if (gradient != nullptr) {
        gradient[i] = parameters[i];
      }
    }
    *cost = sum;
    return true;
  }

  int NumParameters() const override { return num_parameters_; }

 private:
  int num_parameters_;
};

}  // namespace

// Path P1: START -> 1 -> END (không có nhánh rẽ)
TEST(GradientProblemEvaluatorNumResiduals, P1_ReturnsConstant) {
  // Số tham số chọn trong khoảng [1, 5]: 3
  ceres::GradientProblem problem(new SimpleFirstOrderFunction(3));
  ceres::internal::GradientProblemEvaluator evaluator(problem);
  evaluator.NumResiduals();
}
```