**A. Test paths**

Hàm `functor() const` chỉ có một câu lệnh `return *functor_;`, không có điểm rẽ nhánh nào.

CFG: `START → 1 → END`, trong đó node 1 là `return *functor_;`.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Hàm không có tham số. Đối tượng được tạo với `FirstOrderFunctor` hợp lệ (con trỏ khác null) và `kNumParameters` = 2 (1 đến 5). | `new QuadraticFunctor`, `kNumParameters = 2` |

**C. Nhánh không test**

Không có nhánh nào bị bỏ. Unit không có điểm rẽ nhánh nên không có nhánh `CHECK` hay nhánh không thể đi tới.

`C2 dự kiến = 0 / 0` (tổng số nhánh bằng 0, nên mọi câu lệnh đều được phủ bởi TC1; dự kiến, chưa chạy thật)

**D. File test**

```cpp
// FILE: u0003_test.cc
#include "gtest/gtest.h"
#include "ceres/autodiff_first_order_function.h"

namespace {

struct QuadraticFunctor {
  template <typename T>
  bool operator()(const T* const x, T* cost) const {
    cost[0] = x[0] * x[0] + x[1] * x[1];
    return true;
  }
};

}  // namespace

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(AutoDiffFirstOrderFunctionFunctorTest, P1_ReturnsFunctorReference) {
  ceres::AutoDiffFirstOrderFunction<QuadraticFunctor, 2> function(
      new QuadraticFunctor);
  const QuadraticFunctor& f = function.functor();
  (void)f;
}
```