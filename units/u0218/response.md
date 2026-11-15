**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `NumResiduals()` của functor trong khoảng 1 đến 5 (số residual của functor động). Hàm không có tham số. | 2 |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh, nên tổng số nhánh là 0 và chỉ cần một test đi qua node 1.
`C2 dự kiến = 0 / 0 (không có nhánh nào, tức 100%)`

**D. File test**

```cpp
// FILE: u0218_test.cc
#include "gtest/gtest.h"
#include "ceres/tiny_solver_autodiff_function.h"

namespace {

// Functor có số residual động: NumResiduals() do functor cung cấp.
struct DynamicResidualsFunctor {
  int NumResiduals() const { return 2; }

  template <typename T>
  bool operator()(const T* parameters, T* residuals) const {
    residuals[0] = parameters[0] + parameters[1];
    residuals[1] = parameters[2] - parameters[0];
    return true;
  }
};

}  // namespace

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(TinySolverAutoDiffFunctionNumResiduals, ReturnsNumResidualsP1) {
  DynamicResidualsFunctor functor;
  ceres::TinySolverAutoDiffFunction<DynamicResidualsFunctor, -1, 3> function(
      functor);
  function.NumResiduals();
}
```