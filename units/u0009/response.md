**A. Test paths**

CFG của unit:
- START → node 1 (`return *functor_;`) → END
- Không có điểm rẽ nhánh nào (không có `if`, vòng lặp, `switch` hay `?:`).

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh (đường đi duy nhất) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có tham số đầu vào. Object được tạo bằng constructor mặc định, `functor_` luôn khác null. Kiểu template: `Functor` có `Plus` và `Minus`, `kAmbientSize = 2`, `kTangentSize = 2`. | `AutoDiffManifold<PlusMinusFunctor, 2, 2> manifold;` rồi gọi `manifold.functor()` một lần |

**C. Nhánh không test**

Không có. Unit không có điểm rẽ nhánh, nên không có nhánh nào cần phủ và không có `CHECK`.

`C2 dự kiến = 0 / 0` (tổng số nhánh là 0, coi như phủ đủ 100%). Đây là giá trị dự kiến, chưa chạy thật. Test này đi qua node 1, nên cũng đạt C1.

**D. File test**

```cpp
// FILE: u0009_test.cc
#include "gtest/gtest.h"
#include "ceres/autodiff_manifold.h"

namespace ceres {
namespace {

// Functor đơn giản cho AutoDiffManifold: Plus và Minus dạng cộng/trừ từng phần tử.
struct PlusMinusFunctor {
  template <typename T>
  bool Plus(const T* x, const T* delta, T* x_plus_delta) const {
    x_plus_delta[0] = x[0] + delta[0];
    x_plus_delta[1] = x[1] + delta[1];
    return true;
  }

  template <typename T>
  bool Minus(const T* y, const T* x, T* y_minus_x) const {
    y_minus_x[0] = y[0] - x[0];
    y_minus_x[1] = y[1] - x[1];
    return true;
  }
};

// TC1 - P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(AutoDiffManifoldFunctorTest, TC1_P1_ReturnFunctorReference) {
  AutoDiffManifold<PlusMinusFunctor, 2, 2> manifold;
  const PlusMinusFunctor& f = manifold.functor();
  (void)f;
}

}  // namespace
}  // namespace ceres
```