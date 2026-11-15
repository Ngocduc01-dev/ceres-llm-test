**A. Test paths**

Hàm không có điểm rẽ nhánh (0 điểm rẽ nhánh, 0 nhánh, không có vòng lặp, không có `CHECK`). Chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh nào (không có điểm rẽ nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `size` từ 1 đến 5; `constant_parameters` là vector rỗng (hợp lệ với mọi `size`) | `size` = 4 (chọn ngẫu nhiên trong khoảng, cố định), `constant_parameters` = {} |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh nên tổng số nhánh là 0 và mọi nhánh (nếu có) đều đã được phủ; path P1 đi qua node 1 đạt phủ toàn bộ câu lệnh.

C2 dự kiến = 0 / 0 (không có nhánh nào; hàm không có điểm rẽ nhánh, coi như đạt 100%)

**D. File test**

```cpp
// FILE: u0340_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

#include <vector>

namespace ceres {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(SubsetManifoldAmbientSizeTest, P1_ReturnsConstancyMaskSize) {
  const int size = 4;
  const std::vector<int> constant_parameters;
  SubsetManifold manifold(size, constant_parameters);
  manifold.AmbientSize();
}

}  // namespace ceres
```