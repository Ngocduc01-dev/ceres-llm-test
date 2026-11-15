**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → END | node 1: đúng (`ownership_ == DO_NOT_TAKE_OWNERSHIP`) |
| P2 | START → 1 → END | node 1: sai (`ownership_ == TAKE_OWNERSHIP`) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `ownership` = `DO_NOT_TAKE_OWNERSHIP` (điều kiện node 1 đúng); `functor` là con trỏ tới object trên stack, không bị xoá khi huỷ | `ownership = DO_NOT_TAKE_OWNERSHIP`, `functor = &stack_functor` |
| TC2 | P2 | `ownership` ≠ `DO_NOT_TAKE_OWNERSHIP`, tức là `TAKE_OWNERSHIP`; `functor` cấp phát bằng `new` để object tự xoá | `ownership = TAKE_OWNERSHIP`, `functor = new DynamicTwoParameterBlockFunctor` |

Unit không có vòng lặp và không có đầu vào số, nên không cần sinh số ngẫu nhiên hay seed. Enum `Ownership` chỉ có 2 giá trị, nên mỗi giá trị được chọn đúng một lần.

**C. Nhánh không test**

Không có nhánh nào bị bỏ. Cả hai nhánh của node 1 đều đi tới được, và unit không có `CHECK`.

`C2 dự kiến = 2 / 2`

**D. File test**

```cpp
// FILE: u0443_test.cc
#include "gtest/gtest.h"
#include "ceres/dynamic_autodiff_cost_function.h"

namespace ceres {
namespace {

// Functor dùng để khởi tạo DynamicAutoDiffCostFunction (hai khối tham số).
struct DynamicTwoParameterBlockFunctor {
  template <typename T>
  bool operator()(T const* const* parameters, T* residuals) const {
    residuals[0] = parameters[0][0] + parameters[1][0];
    return true;
  }
};

// Path P1: node 1: đúng -> node 2 -> END
TEST(DynamicAutoDiffCostFunctionDestructorTest, DoNotTakeOwnershipReleasesFunctor) {
  DynamicTwoParameterBlockFunctor functor;  // đối tượng trên stack, không được delete
  {
    DynamicAutoDiffCostFunction<DynamicTwoParameterBlockFunctor> cost_function(
        &functor, DO_NOT_TAKE_OWNERSHIP);
  }  // destructor chạy ở đây
  SUCCEED();
}

// Path P2: node 1: sai -> END
TEST(DynamicAutoDiffCostFunctionDestructorTest, TakeOwnershipDeletesFunctor) {
  {
    DynamicAutoDiffCostFunction<DynamicTwoParameterBlockFunctor> cost_function(
        new DynamicTwoParameterBlockFunctor, TAKE_OWNERSHIP);
  }  // destructor chạy ở đây, functor được xoá tự động
  SUCCEED();
}

}  // namespace
}  // namespace ceres
```