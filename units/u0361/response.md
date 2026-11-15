**A. Test paths**

Hàm không có điểm rẽ nhánh (0 điểm rẽ nhánh, 0 nhánh). CFG khớp với mã nguồn. Chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh (không có điểm rẽ nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `size`: 1 đến 5; `index`: 0 đến 5; `user_state`: mảng double tối đa 5 phần tử | `size = 3`, `index = 2`, `user_state = {1.0, 2.0, 3.0}` |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh nên không có nhánh nào bị bỏ qua, và không có `CHECK`.

`C2 dự kiến = 0 / 0` (tổng số nhánh là 0, nên mọi đường đi đều được phủ; 1 test đi qua node 1 là đủ, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0361_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ParameterBlockSetConstantTest, TC1_SetConstantPathP1) {
  double values[3] = {1.0, 2.0, 3.0};
  ParameterBlock parameter_block(values, 3, 2);
  parameter_block.SetConstant();
}

}  // namespace internal
}  // namespace ceres
```