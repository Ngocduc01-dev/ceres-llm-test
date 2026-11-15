**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh. Node 1 chỉ chạy `return (lower_bounds_ == nullptr)`. |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `size` từ 1 đến 5, `index` từ 0 đến 5, `user_state` là mảng double có 5 phần tử. Không có điều kiện đường đi nào ràng buộc thêm. | `size = 3`, `index = 0`, `user_state = {1.0, 2.0, 3.0, 4.0, 5.0}` (cố định, không dùng số ngẫu nhiên) |

**C. Nhánh không test**

- Không có. Hàm không có điểm rẽ nhánh, và biểu thức `lower_bounds_ == nullptr` không phải là một điểm rẽ nhánh.
- CFG khớp với mã nguồn.
- `C2 dự kiến = 0 / 0` (không có nhánh nào cần phủ, coi như đạt 100%; dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0364_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

// TC1 - P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ParameterBlockIsLowerBounded, TC1_P1_NoBranch) {
  double user_state[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
  ceres::internal::ParameterBlock parameter_block(user_state, 3, 0);
  static_cast<void>(parameter_block.IsLowerBounded());
}
```