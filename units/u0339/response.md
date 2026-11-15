**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `num_parameters` từ 1 đến 5; `max_num_corrections` từ 1 đến 5; `use_approximate_eigenvalue_scaling` ∈ {true, false} | `num_parameters` = 3; `max_num_corrections` = 4; `use_approximate_eigenvalue_scaling` = true |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh và không có `CHECK`.

C2 dự kiến = 0 / 0 (tổng số nhánh là 0, nên mọi nhánh đều được phủ; một test đi qua node 1 là đủ).

**D. File test**

```cpp
// FILE: u0339_test.cc
#include "gtest/gtest.h"
#include "ceres/low_rank_inverse_hessian.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(LowRankInverseHessianNumCols, P1_ReturnsNumParameters) {
  ceres::internal::LowRankInverseHessian hessian(3, 4, true);
  hessian.num_cols();
}
```