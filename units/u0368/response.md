**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh (đường đi duy nhất) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `state_offset` là `int` bất kỳ (không có điều kiện ràng buộc) → chọn trong [0, 100]; `user_state` trỏ mảng 1–5 phần tử, `size` = 3, `index` = 0 | `state_offset` = 42 (chọn ngẫu nhiên trong khoảng, cố định); `size` = 3; `index` = 0 |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh và không có vòng lặp, nên không cần xét số lần lặp.
`C2 dự kiến = 0 / 0` (không có nhánh nào; đường đi P1 phủ 100% câu lệnh, node 1).

**D. File test**

```cpp
// FILE: u0368_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ParameterBlockSetStateOffset, P1_AssignStateOffset) {
  double values[3] = {1.0, 2.0, 3.0};
  ceres::internal::ParameterBlock block(values, 3, 0);
  block.set_state_offset(42);
}
```