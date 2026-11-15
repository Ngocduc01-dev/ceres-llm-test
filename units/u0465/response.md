**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | node 1: đúng |
| P2 | START → 1 → 2 → END | node 1: sai, node 2: chạy `release()` |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `ownership` = `TAKE_OWNERSHIP`. Hàm cost và conditioner phải cấp phát bằng `new`, vì destructor sẽ xoá chúng. Số residual của hàm cost là 1 và `conditioners.size()` = 1. | `TAKE_OWNERSHIP`; 1 residual, 1 khối tham số kích thước 1; 1 conditioner cấp phát bằng `new` |
| TC2 | P2 | `ownership` = `DO_NOT_TAKE_OWNERSHIP`. Các đối tượng nằm trên stack, vì destructor không xoá chúng. | `DO_NOT_TAKE_OWNERSHIP`; 1 residual, 1 khối tham số kích thước 1; 1 conditioner trên stack |

Không có giá trị ngẫu nhiên nào được dùng, nên không cần seed. Unit không có vòng lặp. Vòng `for` bên trong `STLDeleteUniqueContainerPointers` không thuộc CFG của unit.

**C. Nhánh không test**

Không có. Cả 2 nhánh đều có test, và `CHECK` nằm ở constructor, không nằm trong unit.

`C2 dự kiến = 2 / 2` (dự kiến, chưa chạy thật)

**D. File test**

```cpp
// FILE: u0465_test.cc
#include "gtest/gtest.h"
#include "ceres/conditioned_cost_function.h"
#include "ceres/stl_util.h"

#include <vector>

namespace ceres {
namespace internal {
namespace {

// Cost function giả: 1 residual, 1 khối tham số kích thước 1.
class DummyCostFunction : public CostFunction {
 public:
  DummyCostFunction() {
    set_num_residuals(1);
    mutable_parameter_block_sizes()->push_back(1);
  }
  bool Evaluate(double const* const* parameters,
                double* residuals,
                double** jacobians) const override {
    residuals[0] = parameters[0][0];
    if (jacobians != nullptr && jacobians[0] != nullptr) {
      jacobians[0][0] = 1.0;
    }
    return true;
  }
};

}  // namespace

// P1: START -> 1 -> END (node 1: đúng)
TEST(ConditionedCostFunctionDestructorTest, TakeOwnership) {
  CostFunction* wrapped = new DummyCostFunction();
  std::vector<CostFunction*> conditioners;
  conditioners.push_back(new DummyCostFunction());
  ConditionedCostFunction* cost_function =
      new ConditionedCostFunction(wrapped, conditioners, TAKE_OWNERSHIP);
  delete cost_function;  // gọi destructor một lần
}

// P2: START -> 1 -> 2 -> END (node 1: sai, node 2: release)
TEST(ConditionedCostFunctionDestructorTest, DoNotTakeOwnership) {
  DummyCostFunction wrapped;
  DummyCostFunction conditioner;
  std::vector<CostFunction*> conditioners;
  conditioners.push_back(&conditioner);
  ConditionedCostFunction* cost_function = new ConditionedCostFunction(
      &wrapped, conditioners, DO_NOT_TAKE_OWNERSHIP);
  delete cost_function;  // gọi destructor một lần
}

}  // namespace internal
}  // namespace ceres
```