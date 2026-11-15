**A. Test paths**

CFG của unit (không có điểm rẽ nhánh nào):

```
START → node 1: `return *functor_;` → END
```

Tổng số điểm rẽ nhánh = 0, nên tổng số nhánh = 0.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `functor_` khác null (constructor nhận con trỏ tới functor hợp lệ); `num_parameters` cố định là 2 (tham số template `kNumParameters = 2`); hệ số `scale` của functor nằm trong [1, 5] | `scale = 3`, chọn bằng `std::mt19937(12345)` với `uniform_int_distribution(1, 5)` |

**C. Nhánh không test**

Không có nhánh nào, nên không có nhánh bị bỏ. Hàm không có vòng lặp, `CHECK` hay điều kiện.

`C2 dự kiến = 0 / 0` (không có nhánh nào; hàm chỉ có 1 đường đi và được phủ hoàn toàn bởi TC1).

**D. File test**

```cpp
// FILE: u0191_test.cc
#include <random>

#include "ceres/numeric_diff_first_order_function.h"
#include "gtest/gtest.h"

namespace ceres {
namespace {

struct QuadraticFunctor {
  explicit QuadraticFunctor(double s) : scale(s) {}
  bool operator()(const double* parameters, double* cost) const {
    cost[0] = scale * (parameters[0] * parameters[0] +
                       parameters[1] * parameters[1]);
    return true;
  }
  double scale;
};

// TC1 - P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(NumericDiffFirstOrderFunctionTest, FunctorReturnsReference) {
  std::mt19937 gen(12345);
  std::uniform_int_distribution<int> dist(1, 5);
  QuadraticFunctor functor(static_cast<double>(dist(gen)));

  NumericDiffFirstOrderFunction<QuadraticFunctor, CENTRAL, 2> function(
      &functor, DO_NOT_TAKE_OWNERSHIP, NumericDiffOptions());

  const QuadraticFunctor& result = function.functor();
  (void)result;
}

}  // namespace
}  // namespace ceres
```