**A. Test paths**

Hàm `state()` không có điểm rẽ nhánh (CFG khớp mã nguồn: node 1 `return state_`). Chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `size` từ 1 đến 5, `index` từ 0 đến 5, `user_state` là mảng double có `size` phần tử | `size = 3`, `index = 2`, `user_state = {1.5, 2.5, 3.5}` |

**C. Nhánh không test**

Không có nhánh nào bị bỏ qua (unit không có điểm rẽ nhánh, không có `CHECK`).

C2 dự kiến = 0 / 0 (không có nhánh nào; mọi câu lệnh đều được chạy qua bởi TC1, tức đạt 100% theo quy ước).

**D. File test**

```cpp
// FILE: u0358_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ParameterBlockStateTest, TC1_ReturnState) {
  double values[3] = {1.5, 2.5, 3.5};
  ceres::internal::ParameterBlock block(values, 3, 2);
  const double* result = block.state();
  (void)result;
}
```