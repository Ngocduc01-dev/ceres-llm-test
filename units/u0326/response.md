**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `NumParameters` = `NumEffectiveParameters` từ 1 đến 5 | 3 |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh và không có `CHECK`.
`C2 dự kiến = 0 / 0` (không có nhánh nào cần phủ; test chạy hết node 1 nên coi như đạt 100%).

Ghi chú: `Evaluator` là lớp trừu tượng và `LineSearchFunction` gọi `evaluator->NumParameters()` trong constructor, nên không thể truyền `nullptr`. Vì vậy file test thêm `#include "ceres/evaluator.h"` để định nghĩa một `Evaluator` giả. Đây là include ngoài mục 3.3 nhưng bắt buộc.

**D. File test**

```cpp
// FILE: u0326_test.cc
#include <map>
#include <memory>
#include <string>

#include "gtest/gtest.h"
#include "ceres/line_search.h"
#include "ceres/evaluator.h"

namespace ceres {
namespace internal {

namespace {

// Evaluator giả, chỉ cung cấp số chiều cho constructor của LineSearchFunction.
class FakeEvaluator : public Evaluator {
 public:
  explicit FakeEvaluator(int n) : n_(n) {}

  std::unique_ptr<SparseMatrix> CreateJacobian() const final {
    return nullptr;
  }

  bool Evaluate(const EvaluateOptions& evaluate_options,
                const double* state,
                double* cost,
                double* residuals,
                double* gradient,
                SparseMatrix* jacobian) final {
    return true;
  }

  bool Plus(const double* state,
            const double* delta,
            double* state_plus_delta) const final {
    return true;
  }

  int NumParameters() const final { return n_; }
  int NumEffectiveParameters() const final { return n_; }
  int NumResiduals() const final { return n_; }

 private:
  int n_;
};

}  // namespace

// TC1 - Path P1: START -> 1 -> END (không có nhánh rẽ)
TEST(LineSearchFunctionDirectionTest, P1_ReturnDirection) {
  FakeEvaluator evaluator(3);
  LineSearchFunction function(&evaluator);
  const Vector& direction = function.direction();
  (void)direction;
}

}  // namespace internal
}  // namespace ceres
```