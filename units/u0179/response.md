**A. Test paths**

Hàm không có điểm rẽ nhánh (0 điểm rẽ nhánh, 0 nhánh). CFG khớp với mã nguồn: `return size_;`.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh nào (đường đi duy nhất) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `size` của `EuclideanManifold<DYNAMIC>` (constructor `EuclideanManifold(int size)`): số nguyên từ 0 đến 5 | 3 (chọn ngẫu nhiên, cố định) |

**C. Nhánh không test**

Không có nhánh nào bị bỏ (hàm không có điểm rẽ nhánh nên không có nhánh cần loại).
`C2 dự kiến = 0 / 0` (không có nhánh; mọi câu lệnh được phủ bởi TC1, tức C1 = 100%).

**D. File test**

```cpp
// FILE: u0179_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

namespace ceres {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(EuclideanManifoldTangentSize, P1_ReturnSize) {
  EuclideanManifold<DYNAMIC> manifold(3);
  manifold.TangentSize();
}

}  // namespace ceres
```