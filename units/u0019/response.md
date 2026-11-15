**A. Test paths**

CFG: `START → 1 → END`
- Node 1: `return *functor_;` (một khối lệnh tuần tự).
- Hàm không có `if`, `for`, `while`, `switch` hay `?:`, nên không có điểm rẽ nhánh và không có vòng lặp.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có tham số đầu vào. Object được tạo với con trỏ functor hợp lệ (khác `nullptr`) và `ownership = DO_NOT_TAKE_OWNERSHIP`. | Functor `SimpleFunctor` cấp phát trên stack, không dùng số ngẫu nhiên. |

**C. Nhánh không test**
- Không có nhánh nào bị bỏ qua. Hàm không có điểm rẽ nhánh và không có `CHECK`.
- C2 dự kiến = 0 / 0 (tổng số nhánh = 0, nên P1 phủ toàn bộ hàm. Đạt C1 khi dòng 267 được chạy).

**D. File test**

```cpp
// FILE: u0019_test.cc
#include "gtest/gtest.h"
#include "ceres/dynamic_autodiff_cost_function.h"

namespace {

struct SimpleFunctor {
  template <typename T>
  bool operator()(T const* const* parameters, T* residuals) const {
    residuals[0] = parameters[0][0];
    return true;
  }
};

}  // namespace

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(DynamicAutoDiffCostFunctionFunctorTest, ReturnsFunctorReference) {
  SimpleFunctor functor;
  ceres::DynamicAutoDiffCostFunction<SimpleFunctor> cost_function(
      &functor, ceres::DO_NOT_TAKE_OWNERSHIP);
  const SimpleFunctor& result = cost_function.functor();
  (void)result;
}
```