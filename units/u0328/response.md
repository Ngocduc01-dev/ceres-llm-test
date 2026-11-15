**A. Test paths**

Hàm không có điểm rẽ nhánh nên chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh (0 nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `num_parameters` (không dùng): 1 đến 5; `num_effective_parameters`: 1 đến 5 | `num_parameters` = 4, `num_effective_parameters` = 3 |

**C. Nhánh không test**

Không có nhánh nào cần bỏ qua, vì hàm không có điểm rẽ nhánh và không có `CHECK`.

`C2 dự kiến = 0 / 0` (không có nhánh nào, nên C2 coi như đạt đầy đủ; một test duy nhất phủ toàn bộ node 1).

**D. File test**

```cpp
// FILE: u0328_test.cc
#include "gtest/gtest.h"
#include "ceres/line_search_minimizer.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(LineSearchMinimizerStateTest, ConstructorTC1) {
  LineSearchMinimizer::State state(4, 3);
}

}  // namespace internal
}  // namespace ceres
```