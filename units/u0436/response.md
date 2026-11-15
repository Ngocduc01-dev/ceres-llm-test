**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → END | node 1: đúng (`ownership_ == DO_NOT_TAKE_OWNERSHIP`) |
| P2 | START → 1 → END | node 1: sai (`ownership_ == TAKE_OWNERSHIP`) |

Hàm không có vòng lặp.

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `ownership` = `DO_NOT_TAKE_OWNERSHIP`. Functor phải nằm ngoài heap và do test quản lý, vì `release()` làm cost function không giữ con trỏ nữa. | `ownership = DO_NOT_TAKE_OWNERSHIP`, functor là biến cục bộ trên stack |
| TC2 | P2 | `ownership` = `TAKE_OWNERSHIP`. Functor cấp phát bằng `new` để destructor tự `delete`. | `ownership = TAKE_OWNERSHIP`, functor = `new BinaryScalarCost` |

Không có đầu vào số nào cần chọn ngẫu nhiên, nên không dùng hàm sinh số ngẫu nhiên.

**C. Nhánh không test**

Không có nhánh nào bị bỏ. Cả 2 nhánh của node 1 đều đi tới được, và hàm không có `CHECK`.

`C2 dự kiến = 2 / 2`

**D. File test**

```cpp
// FILE: u0436_test.cc
#include "gtest/gtest.h"
#include "ceres/autodiff_cost_function.h"

namespace {

// Functor 1 residual, 2 tham số block kích thước 2 và 2.
struct BinaryScalarCost {
  template <typename T>
  bool operator()(const T* x, const T* y, T* residual) const {
    residual[0] = x[0] * y[0] + x[1] * y[1];
    return true;
  }
};

}  // namespace

// Path P1: START -> 1 -> 2 -> END (node 1: đúng)
TEST(AutoDiffCostFunctionDestructorTest, DoNotTakeOwnershipReleasesFunctor) {
  BinaryScalarCost functor;  // do test quản lý, không để cost function delete
  auto* cost_function =
      new ceres::AutoDiffCostFunction<BinaryScalarCost, 1, 2, 2>(
          &functor, ceres::DO_NOT_TAKE_OWNERSHIP);
  delete cost_function;  // gọi ~AutoDiffCostFunction()
}

// Path P2: START -> 1 -> END (node 1: sai)
TEST(AutoDiffCostFunctionDestructorTest, TakeOwnershipDeletesFunctor) {
  auto* cost_function =
      new ceres::AutoDiffCostFunction<BinaryScalarCost, 1, 2, 2>(
          new BinaryScalarCost, ceres::TAKE_OWNERSHIP);
  delete cost_function;  // gọi ~AutoDiffCostFunction()
}
```