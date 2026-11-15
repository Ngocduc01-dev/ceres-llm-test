**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm rẽ nhánh, tổng số nhánh = 0). Chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `size` từ 1 đến 5; `index` từ 0 đến 5; `user_state` là mảng `double` 5 phần tử | `size = 3`, `index = 2`, `user_state = {1.0, 2.0, 3.0, 4.0, 5.0}` (cố định, không dùng số ngẫu nhiên) |

**C. Nhánh không test**

Không có nhánh nào bị bỏ (hàm không có điểm rẽ nhánh). CFG khớp với mã nguồn.

`C2 dự kiến = 0 / 0` (không có nhánh; test chạy qua node 1, phủ toàn bộ câu lệnh của hàm).

**D. File test**

```cpp
// FILE: u0369_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ParameterBlockDeltaOffsetTest, P1_ReturnDeltaOffset) {
  double user_state[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
  ParameterBlock block(user_state, 3, 2);
  block.delta_offset();
}

}  // namespace internal
}  // namespace ceres
```