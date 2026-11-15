**A. Test paths**

CFG: `START → 1 [return *functor_;] → END`. Hàm không có điểm rẽ nhánh (không có if, vòng lặp, switch hay ?:), nên chỉ có một đường đi.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `num_residuals` phải bằng số residual tĩnh (1), nên khoảng là {1}. `functor` là con trỏ khác null tới `CostFunctor`. `ownership` ∈ {TAKE_OWNERSHIP, DO_NOT_TAKE_OWNERSHIP}. `options` là `NumericDiffOptions` mặc định. | `num_residuals = 1`, `functor = new SimpleFunctor`, `ownership = TAKE_OWNERSHIP`, `options` mặc định. Không dùng số ngẫu nhiên nên không cần seed. |

**C. Nhánh không test**

Không có nhánh nào bị bỏ qua, vì hàm không có điểm rẽ nhánh và không có `CHECK`.

`C2 dự kiến = 0 / 0` (không có nhánh nào cần phủ; coi như 100%, và dòng 250 được chạy qua bởi TC1).

**D. File test**

```cpp
// FILE: u0189_test.cc
#include "gtest/gtest.h"
#include "ceres/numeric_diff_cost_function.h"

namespace {

struct SimpleFunctor {
  bool operator()(const double* x, double* residual) const {
    residual[0] = x[0];
    return true;
  }
};

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(NumericDiffCostFunctionFunctorTest, P1_ReturnsFunctorReference) {
  ceres::NumericDiffOptions options;
  ceres::NumericDiffCostFunction<SimpleFunctor, ceres::CENTRAL, 1, 1>
      cost_function(new SimpleFunctor, ceres::TAKE_OWNERSHIP, 1, options);

  const SimpleFunctor& f = cost_function.functor();
  (void)f;
}

}  // namespace
```