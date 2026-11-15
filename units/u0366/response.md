**A. Test paths**

Hàm có 0 điểm rẽ nhánh (CFG chỉ có node 1, khớp với mã nguồn), nên chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `index` là mọi số nguyên `int` (không có điều kiện ràng buộc); dùng khoảng 0..100. Constructor: `user_state` trỏ mảng `double[3]`, `size = 3`, `index = -1` | `index = 37` (cố định, đại diện cho khoảng 0..100) |

**C. Nhánh không test**

Không có nhánh nào (hàm không có điểm rẽ nhánh, không có vòng lặp, không có `CHECK`).
`C2 dự kiến = 0 / 0` (tổng số nhánh = 0, nên C2 được xem là đạt 100% do mọi câu lệnh ở node 1 đều được chạy).

**D. File test**

```cpp
// FILE: u0366_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ParameterBlockSetIndexTest, SetsIndexOnce) {
  double values[3] = {1.0, 2.0, 3.0};
  ParameterBlock block(values, 3, -1);
  block.set_index(37);
}

}  // namespace internal
}  // namespace ceres
```