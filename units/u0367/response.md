**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh (chỉ có node 1: `return state_offset_`) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `user_state`: mảng double 1–5 phần tử; `size` từ 1 đến 5 (bằng số phần tử mảng); `index` từ 0 đến 5 | mảng 3 phần tử `{1.0, 2.0, 3.0}`, `size = 3`, `index = 2` |

**C. Nhánh không test**

Không có (hàm không có điểm rẽ nhánh nên tổng số nhánh = 0, không có nhánh nào bị bỏ qua).
`C2 dự kiến = 0 / 0` (không có nhánh; toàn bộ đường đi START → 1 → END được chạy qua, tức coi như đạt 100%).

**D. File test**

```cpp
// FILE: u0367_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ParameterBlockStateOffsetTest, TC1_ReturnStateOffset) {
  double values[3] = {1.0, 2.0, 3.0};
  ParameterBlock parameter_block(values, 3, 2);
  // Chỉ gọi hàm, không kiểm tra kết quả trả về.
  int offset = parameter_block.state_offset();
  (void)offset;
}

}  // namespace internal
}  // namespace ceres
```