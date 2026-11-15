**A. Test paths**

Hàm không có điểm rẽ nhánh (0 điểm rẽ nhánh, 0 nhánh). CFG khớp với mã nguồn.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh; node 1: `is_set_constant_ = false` |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `size` ∈ [1, 5], `index` ∈ [0, 5], `user_state` là mảng double có `size` phần tử | `size = 3`, `index = 2`, `user_state = {1.0, 2.0, 3.0}` |

**C. Nhánh không test**

Không có nhánh nào bị bỏ (hàm không có điểm rẽ nhánh, không có `CHECK`).

`C2 dự kiến = 0 / 0` (không có nhánh nào; toàn bộ node 1 được chạy qua bởi TC1, nên C1 = 100%).

**D. File test**

```cpp
// FILE: u0362_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

// Path P1: START -> 1 -> END
TEST(ParameterBlockSetVarying, SetVaryingPathP1) {
  double user_state[3] = {1.0, 2.0, 3.0};
  ceres::internal::ParameterBlock parameter_block(user_state, 3, 2);
  parameter_block.SetVarying();
}
```