**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh (chỉ có một đường đi duy nhất) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `user_state`: con trỏ tới mảng double hợp lệ; `size` từ 1 đến 5; `index` từ 0 đến 5 | mảng 3 phần tử `{1.0, 2.0, 3.0}`; `size = 3`; `index = 2` (chọn ngẫu nhiên, cố định) |

**C. Nhánh không test:** không có (hàm không có điểm rẽ nhánh, không có `CHECK`, không có vòng lặp).
`C2 dự kiến = 0 / 0` (tổng số nhánh = 0, nên mọi nhánh đều đã được phủ bởi đường đi duy nhất P1).

**D. File test**

```cpp
// FILE: u0360_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END
TEST(ParameterBlockMutableUserStateTest, ReturnsUserState_P1) {
  double values[3] = {1.0, 2.0, 3.0};
  ParameterBlock block(values, 3, 2);
  double* state = block.mutable_user_state();
  (void)state;
}

}  // namespace internal
}  // namespace ceres
```