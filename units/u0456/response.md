**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → END | node 1: đúng |
| P2 | START → 1 → END | node 1: sai |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `ownership` ≠ `TAKE_OWNERSHIP`, tức chỉ có `DO_NOT_TAKE_OWNERSHIP` | `DO_NOT_TAKE_OWNERSHIP`, functor cấp phát trên stack |
| TC2 | P2 | `ownership` = `TAKE_OWNERSHIP` | `TAKE_OWNERSHIP`, functor cấp phát bằng `new` |

**C. Nhánh không test**

Không có. Không có `CHECK` và không có vòng lặp trong unit. Hai nhánh của node 1 đều có test.

CFG khớp với mã nguồn. Ghi chú: `QuadraticCostFunctor` không nằm trong các `#include` ở mục 3.3, nên file test tự định nghĩa một functor cùng tên.

C2 dự kiến = 2 / 2

**D. File test**

```cpp
// FILE: u0456_test.cc
#include "gtest/gtest.h"
#include "ceres/numeric_diff_first_order_function.h"

namespace ceres {
namespace {

// Functor 4 tham số, trả về cost = tổng bình phương các tham số.
struct QuadraticCostFunctor {
  bool operator()(const double* parameters, double* cost) const {
    double sum = 0.0;
    for (int i = 0; i < 4; ++i) {
      sum += parameters[i] * parameters[i];
    }
    *cost = sum;
    return true;
  }
};

// P1: node 1: đúng (ownership_ != TAKE_OWNERSHIP) -> node 2 -> END
TEST(NumericDiffFirstOrderFunctionDtorTest, DoNotTakeOwnership) {
  QuadraticCostFunctor functor;  // sống trên stack, destructor không được delete
  {
    NumericDiffFirstOrderFunction<QuadraticCostFunctor, CENTRAL, 4> function(
        &functor, DO_NOT_TAKE_OWNERSHIP, NumericDiffOptions());
  }  // destructor chạy tại đây
  SUCCEED();
}

// P2: node 1: sai (ownership_ == TAKE_OWNERSHIP) -> END
TEST(NumericDiffFirstOrderFunctionDtorTest, TakeOwnership) {
  QuadraticCostFunctor* functor = new QuadraticCostFunctor();
  {
    NumericDiffFirstOrderFunction<QuadraticCostFunctor, CENTRAL, 4> function(
        functor, TAKE_OWNERSHIP, NumericDiffOptions());
  }  // destructor chạy tại đây, functor_ (unique_ptr) tự giải phóng
  SUCCEED();
}

}  // namespace
}  // namespace ceres
```