**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm rẽ nhánh, 0 nhánh). CFG khớp với mã nguồn. Chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh (node 1: `return index_`) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `size` từ 1 đến 5; `index` từ 0 đến 5 (không có điều kiện ràng buộc từ đường đi) | `size = 3`, `index = 2`, `user_state` là mảng 3 phần tử double |

**C. Nhánh không test**

Không có. Hàm không có nhánh nào cần bỏ qua và không có `CHECK`.

`C2 dự kiến = 0 / 0` (hàm không có điểm rẽ nhánh nên không có nhánh; node 1 được phủ bởi TC1, tức độ phủ C2 coi như đạt 100%).

**D. File test**

```cpp
// FILE: u0365_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ParameterBlockIndexTest, P1_ReturnIndex) {
  double values[3] = {1.0, 2.0, 3.0};
  ParameterBlock block(values, 3, 2);
  block.index();
}

}  // namespace internal
}  // namespace ceres
```