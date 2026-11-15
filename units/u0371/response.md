**A. Test paths**

Hàm không có điểm rẽ nhánh (0 điểm rẽ nhánh, 0 nhánh), nên chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `size` từ 1 đến 5; `index` từ 0 đến 5; `user_state` là mảng double có `size` phần tử | `size` = 3, `index` = 2, `user_state` = {0.5, 1.5, 2.5} (chọn cố định, không dùng số ngẫu nhiên nên không cần seed) |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh nên không có nhánh nào cần phủ và không có `CHECK` nào bị bỏ qua.

C2 dự kiến = 0 / 0 (không có nhánh; test duy nhất đi qua toàn bộ đường START → 1 → END, nên C1 đạt 100%)

**D. File test**

```cpp
// FILE: u0371_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ParameterBlockPlusJacobian, P1_NoBranch) {
  double user_state[3] = {0.5, 1.5, 2.5};
  ceres::internal::ParameterBlock block(user_state, 3, 2);
  const double* result = block.PlusJacobian();
  (void)result;
}
```