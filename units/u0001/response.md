**A. Test paths**

Hàm `functor() const` chỉ có một lệnh `return *functor_;`. Không có `if`, vòng lặp, `switch` hay `?:`, nên không có điểm rẽ nhánh.

CFG: `START → 1 → END`. Node 1 là `return *functor_;`.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có tham số đầu vào cho `functor()`. Object được tạo với con trỏ functor hợp lệ (khác null) và `Ownership = DO_NOT_TAKE_OWNERSHIP`. | Functor `F` cục bộ trên stack, 1 residual, 1 tham số kích thước 1. Không cần số ngẫu nhiên. |

**C. Nhánh không test**

Không có. Unit không có nhánh nào và không có `CHECK`.

`C2 dự kiến = 0 / 0` (không có nhánh nào, mọi câu lệnh được phủ bởi TC1; chưa chạy thật).

**D. File test**

```cpp
// FILE: u0001_test.cc
#include "gtest/gtest.h"
#include "ceres/autodiff_cost_function.h"

namespace {

struct SimpleFunctor {
  template <typename T>
  bool operator()(const T* const x, T* residual) const {
    residual[0] = x[0];
    return true;
  }
};

}  // namespace

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(AutoDiffCostFunctionFunctorTest, TC1_ReturnsFunctorReference) {
  SimpleFunctor functor;
  ceres::AutoDiffCostFunction<SimpleFunctor, 1, 1> cost_function(
      &functor, ceres::DO_NOT_TAKE_OWNERSHIP);
  const SimpleFunctor& result = cost_function.functor();
  (void)result;
}
```