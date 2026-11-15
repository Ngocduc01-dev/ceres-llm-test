**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → END | node 1: đúng |
| P2 | START → 1 → END | node 1: sai |

CFG khớp với mã nguồn. Hàm không có vòng lặp và không có `CHECK`.

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `ownership` = `DO_NOT_TAKE_OWNERSHIP` (điều kiện `ownership_ != TAKE_OWNERSHIP` đúng). Functor tạo trên stack. | `DO_NOT_TAKE_OWNERSHIP` |
| TC2 | P2 | `ownership` = `TAKE_OWNERSHIP` (điều kiện sai). Functor cấp phát bằng `new`, object sẽ `delete` nó. | `TAKE_OWNERSHIP` |

Đầu vào duy nhất ảnh hưởng nhánh là `ownership`. Nó là enum có đúng 2 giá trị nên không cần chọn ngẫu nhiên và không cần seed.

**C. Nhánh không test**

Không có nhánh nào bị bỏ.

`C2 dự kiến = 2 / 2`

**D. File test**

```cpp
// FILE: u0444_test.cc
#include "gtest/gtest.h"
#include "ceres/dynamic_numeric_diff_cost_function.h"

namespace {

struct PlusFunctor {
  bool operator()(double const* const* parameters, double* residuals) const {
    residuals[0] = parameters[0][0] + parameters[0][1];
    return true;
  }
};

}  // namespace

// Path P1: node 1: đúng -> node 2 -> END
TEST(DynamicNumericDiffCostFunctionDtorTest, DoNotTakeOwnership) {
  PlusFunctor functor;  // sống trên stack, object không được xoá nó
  {
    ceres::DynamicNumericDiffCostFunction<PlusFunctor, ceres::RIDDERS>
        cost_function(&functor,
                      ceres::DO_NOT_TAKE_OWNERSHIP,
                      ceres::NumericDiffOptions());
  }  // destructor chạy tại đây
}

// Path P2: node 1: sai -> END
TEST(DynamicNumericDiffCostFunctionDtorTest, TakeOwnership) {
  PlusFunctor* functor = new PlusFunctor();  // object sở hữu và tự xoá
  {
    ceres::DynamicNumericDiffCostFunction<PlusFunctor, ceres::RIDDERS>
        cost_function(functor,
                      ceres::TAKE_OWNERSHIP,
                      ceres::NumericDiffOptions());
  }  // destructor chạy tại đây
}
```