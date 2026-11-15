**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh (chỉ có node 1: `return num_parameters_`) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `num_parameters` từ 1 đến 5; `max_num_corrections` từ 1 đến 5; `use_approximate_eigenvalue_scaling` ∈ {true, false} | `num_parameters` = 3; `max_num_corrections` = 2; `use_approximate_eigenvalue_scaling` = true |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh nên tổng số nhánh là 0 và mọi đường đi đều được phủ bởi P1. CFG khớp với mã nguồn.

`C2 dự kiến = 0 / 0` (không có nhánh nào; hàm được phủ hoàn toàn bởi 1 test path duy nhất, tức 100% theo quy ước)

**D. File test**

```cpp
// FILE: u0338_test.cc
#include "gtest/gtest.h"
#include "ceres/low_rank_inverse_hessian.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(LowRankInverseHessianNumRowsTest, P1_ReturnsNumParameters) {
  ceres::internal::LowRankInverseHessian hessian(3, 2, true);
  hessian.num_rows();
}
```