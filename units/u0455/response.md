**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → END | node 1: đúng (`ownership_ != TAKE_OWNERSHIP`) |
| P2 | START → 1 → END | node 1: sai (`ownership_ == TAKE_OWNERSHIP`) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `ownership` = `DO_NOT_TAKE_OWNERSHIP` (khác `TAKE_OWNERSHIP`). `functor` là đối tượng trên stack, vì `release()` sẽ không xoá nó. `num_residuals` = 3 (khớp tham số template). | `DO_NOT_TAKE_OWNERSHIP`, functor trên stack, `num_residuals` = 3, `NumericDiffOptions()` mặc định |
| TC2 | P2 | `ownership` = `TAKE_OWNERSHIP`. `functor` cấp phát bằng `new` để object tự xoá. `num_residuals` = 3. | `TAKE_OWNERSHIP`, `new` functor, `num_residuals` = 3, `NumericDiffOptions()` mặc định |

Không có đầu vào ngẫu nhiên nên không cần seed. Unit không có vòng lặp.

**C. Nhánh không test**

Không có. Mọi nhánh đều đi tới được.

`C2 dự kiến = 2 / 2` (dự kiến, chưa chạy thật)

**D. File test**

```cpp
// FILE: u0455_test.cc
#include "gtest/gtest.h"
#include "ceres/numeric_diff_cost_function.h"

namespace {

// Functor đơn giản: 2 khối tham số kích thước 5, 5 và 3 residual.
struct EasyFunctor {
  bool operator()(const double* x1, const double* x2, double* residuals) const {
    residuals[0] = x1[0] + x2[0];
    residuals[1] = x1[1] * x2[1];
    residuals[2] = x1[2] - x2[2];
    return true;
  }
};

using CostFn = ceres::NumericDiffCostFunction<EasyFunctor, ceres::CENTRAL, 3, 5, 5>;

// P1: node 1: đúng -> node 2 (functor_.release()) -> END
TEST(NumericDiffCostFunctionDestructorTest, DoNotTakeOwnershipReleasesFunctor) {
  EasyFunctor functor;  // trên stack, release() nên không bị xoá
  {
    CostFn cost_function(
        &functor, ceres::DO_NOT_TAKE_OWNERSHIP, 3, ceres::NumericDiffOptions());
  }  // destructor chạy ở đây
}

// P2: node 1: sai -> END
TEST(NumericDiffCostFunctionDestructorTest, TakeOwnershipKeepsFunctor) {
  {
    CostFn cost_function(
        new EasyFunctor, ceres::TAKE_OWNERSHIP, 3, ceres::NumericDiffOptions());
  }  // destructor chạy ở đây, unique_ptr tự xoá functor
}

}  // namespace
```