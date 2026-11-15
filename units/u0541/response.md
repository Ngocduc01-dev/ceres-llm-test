**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → END | node 1: đúng, node 2: đúng |
| P2 | START → 1 → 2 → 4 → 5 → 6 → END | node 1: đúng, node 2: sai (vế `!lower_bounds_` đúng, vế `lower_bound <= -max` sai), node 4: đúng |
| P3 | START → 1 → 2 → 4 → 6 → END | node 1: đúng, node 2: sai (vế `!lower_bounds_` sai), node 4: sai |

Hàm không có vòng lặp nào (`std::fill` là lời gọi thư viện, không phải điểm rẽ nhánh trong CFG), nên không có yêu cầu về số lần lặp.

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `size_=3`, `lower_bounds_` chưa cấp phát (object mới); `index` ∈ [0,2]; `lower_bound` ≤ -max, tức chỉ nhận -max hoặc -∞ | index = 1, lower_bound = -max |
| TC2 | P2 | `lower_bounds_` chưa cấp phát; `index` ∈ [0,2]; `lower_bound` > -max | index = 2, lower_bound = 3.7 |
| TC3 | P3 | `lower_bounds_` đã cấp phát (nhờ 1 lần gọi chuẩn bị với giá trị > -max); `index` ∈ [0,2]; `lower_bound` bất kỳ | chuẩn bị: index = 0, lower_bound = -2.5; gọi chính: index = 1, lower_bound = -max |

Giá trị được chọn cố định, không dùng hàm sinh số ngẫu nhiên. Ở TC3, `lower_bound` = -max làm vế đầu của node 2 đúng và vế `!lower_bounds_` sai, nên node 2 đi nhánh sai.

**C. Nhánh không test**

- CHECK_LT ở node 1 sai: không test (làm chương trình dừng). Nhánh này không nằm trong tổng số nhánh.
- Lưu ý: không có cách nào khác để cấp phát `lower_bounds_` ngoài chính `SetLowerBound`. TC3 vì vậy phải gọi hàm 1 lần để chuẩn bị trước lần gọi chính.

C2 dự kiến = 4 / 4

**D. File test**

```cpp
// FILE: u0541_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

namespace ceres {
namespace internal {

// Path P1: node 1: đúng, node 2: đúng (lower_bound <= -max và lower_bounds_ chưa cấp phát) -> return
TEST(ParameterBlockSetLowerBoundTest, P1_EarlyReturnWhenNoBoundsAndLowest) {
  double values[3] = {1.0, 2.0, 3.0};
  ParameterBlock block(values, 3, 0);
  block.SetLowerBound(1, -std::numeric_limits<double>::max());
}

// Path P2: node 1: đúng, node 2: sai, node 4: đúng -> cấp phát và gán
TEST(ParameterBlockSetLowerBoundTest, P2_AllocateBoundsThenAssign) {
  double values[3] = {1.0, 2.0, 3.0};
  ParameterBlock block(values, 3, 0);
  block.SetLowerBound(2, 3.7);
}

// Path P3: node 1: đúng, node 2: sai (lower_bounds_ đã có), node 4: sai -> chỉ gán
TEST(ParameterBlockSetLowerBoundTest, P3_AssignWhenBoundsAlreadyAllocated) {
  double values[3] = {1.0, 2.0, 3.0};
  ParameterBlock block(values, 3, 0);
  block.SetLowerBound(0, -2.5);  // chuẩn bị: cấp phát lower_bounds_
  block.SetLowerBound(1, -std::numeric_limits<double>::max());
}

}  // namespace internal
}  // namespace ceres
```