**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → END | node 1: đúng |
| P2 | START → 1 → END | node 1: sai |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `x != state_`: `x` là mảng khác `user_state`, `size` từ 1 đến 5 | `size = 3`, `user_state = {1.0, 2.0, 3.0}`, `x = {0.0, 0.0, 0.0}` (mảng khác) |
| TC2 | P2 | `x == state_`: truyền chính `user_state` (khi khởi tạo `state_ = user_state`), `size` từ 1 đến 5 | `size = 4`, `user_state = {5.0, 6.0, 7.0, 8.0}`, `x = user_state` |

**C. Nhánh không test**

- Không có. Hàm không có vòng lặp và không có `CHECK`. CFG khớp với mã nguồn.
- C2 dự kiến = 2 / 2

**D. File test**

```cpp
// FILE: u0479_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> 2 -> END (node 1: đúng)
TEST(ParameterBlockGetStateTest, P1_XDifferentFromState) {
  double user_state[3] = {1.0, 2.0, 3.0};
  double x[3] = {0.0, 0.0, 0.0};
  ParameterBlock block(user_state, 3, 0);
  block.GetState(x);
}

// Path P2: START -> 1 -> END (node 1: sai)
TEST(ParameterBlockGetStateTest, P2_XEqualsState) {
  double user_state[4] = {5.0, 6.0, 7.0, 8.0};
  ParameterBlock block(user_state, 4, 0);
  block.GetState(user_state);
}

}  // namespace internal
}  // namespace ceres
```