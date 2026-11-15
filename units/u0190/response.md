**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Số tham số của template cố định `kNumParameters = 4`. Không có đầu vào nào khác ảnh hưởng đến đường đi. | `NumericDiffFirstOrderFunction<QuadraticCostFunctor, CENTRAL, 4>`, `NumericDiffOptions()` mặc định |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh và không có vòng lặp, nên một test path P1 là đủ.
Mã nguồn khớp với CFG (node 1: `return num_parameters_`).

`C2 dự kiến = 0 / 0` (không có nhánh nào; mọi câu lệnh của hàm đều được chạy, tức là 100% theo quy ước).

**D. File test**

```cpp
// FILE: u0190_test.cc
#include "gtest/gtest.h"
#include "ceres/numeric_diff_first_order_function.h"

namespace ceres {
namespace {

// Functor bậc nhất đơn giản với 4 tham số.
struct QuadraticCostFunctor {
  bool operator()(const double* parameters, double* cost) const {
    double sum = 0.0;
    for (int i = 0; i < 4; ++i) {
      sum += parameters[i] * parameters[i];
    }
    *cost = sum;
    return true;
  }
};

// Path P1: START -> 1 -> END (không có nhánh rẽ)
TEST(NumericDiffFirstOrderFunctionNumParametersTest, TC1_ReturnNumParameters) {
  NumericDiffOptions options;
  NumericDiffFirstOrderFunction<QuadraticCostFunctor, CENTRAL, 4> function(
      new QuadraticCostFunctor(), TAKE_OWNERSHIP, options);
  function.NumParameters();
}

}  // namespace
}  // namespace ceres
```