**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh (chỉ một đường đi duy nhất) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `size` từ 1 đến 5; `index` từ 0 đến 5; `user_state` trỏ tới mảng double có ít nhất `size` phần tử | `size = 3`, `index = 2`, `user_state = {1.0, 2.0, 3.0}` |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh nào, nên không có nhánh bị bỏ qua.

`C2 dự kiến = 0 / 0` (tổng số nhánh bằng 0, nên đường đi duy nhất P1 được chạy qua là đã phủ toàn bộ; coi như 100%).

**D. File test**

```cpp
// FILE: u0372_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

// Path P1: START -> 1 -> END
TEST(ParameterBlockMutableResidualBlocksTest, P1_ReturnsResidualBlocksPointer) {
  double values[3] = {1.0, 2.0, 3.0};
  ceres::internal::ParameterBlock block(values, 3, 2);
  ceres::internal::ParameterBlock::ResidualBlockSet* result =
      block.mutable_residual_blocks();
  (void)result;
}
```

Lưu ý: `ResidualBlockSet` có thể không là kiểu lồng trong `ParameterBlock` ở mã nguồn thật. Nếu biên dịch lỗi, thay dòng khai báo `result` bằng `auto* result = block.mutable_residual_blocks();`. Để tránh rủi ro, đây là phiên bản an toàn hơn, nên dùng thay thế:

```cpp
// FILE: u0372_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

// Path P1: START -> 1 -> END
TEST(ParameterBlockMutableResidualBlocksTest, P1_ReturnsResidualBlocksPointer) {
  double values[3] = {1.0, 2.0, 3.0};
  ceres::internal::ParameterBlock block(values, 3, 2);
  auto* result = block.mutable_residual_blocks();
  (void)result;
}
```