**A. Test paths**

Hàm có 0 điểm rẽ nhánh và chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `x` là 1 phần tử, thuộc [-5, 5], không có điều kiện đường đi. `parameters` là mảng con trỏ chứa `&x`. `cost` là con trỏ tới 1 double hợp lệ. | `x = 3.0` (seed cố định bằng cách gán trực tiếp), `cost` khởi tạo 0.0 |

Hàm không có vòng lặp nên không cần test số lần lặp.

**C. Nhánh không test**

Không có nhánh nào bị bỏ qua, vì hàm không có điểm rẽ nhánh và không có `CHECK`. Mã nguồn khớp với CFG (một lệnh `return functor_(*parameters, cost)`).

`C2 dự kiến = 0 / 0` (không có nhánh nào để phủ; TC1 đi qua node 1 duy nhất; dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0067_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/variadic_evaluate.h"

namespace ceres {
namespace internal {

namespace {

// Functor bậc nhất đơn giản: cost = x^2 (nhận một khối tham số).
struct QuadraticCostFunctor {
  bool operator()(const double* x, double* cost) const {
    cost[0] = x[0] * x[0];
    return true;
  }
};

}  // namespace

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(FirstOrderFunctorAdapterTest, TC1_CallFunctorOnce) {
  QuadraticCostFunctor functor;
  FirstOrderFunctorAdapter<QuadraticCostFunctor> adapter(functor);

  double x[1] = {3.0};
  const double* parameters[1] = {x};
  double cost = 0.0;

  (void)adapter(parameters, &cost);
}

}  // namespace internal
}  // namespace ceres
```