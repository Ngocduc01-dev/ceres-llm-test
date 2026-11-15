**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `SubsetManifold(size, constant_parameters)`: size từ 2 đến 5, constant_parameters là tập chỉ số trong [0, size) (không trùng, không phải toàn bộ). Hai manifold giống nhau. | size = 3, constant_parameters = {1} (cho cả hai manifold) |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh nên tổng số nhánh = 0; không có nhánh `CHECK` nào.
`C2 dự kiến = 0 / 0` (không có nhánh; test chỉ phủ node 1 → END, tức C1 = 100%; dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0199_test.cc
#include "gtest/gtest.h"
#include "ceres/product_manifold.h"

#include <vector>

namespace ceres {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ProductManifoldAmbientSizeTest, P1_ReturnAmbientSize) {
  std::vector<int> constant_parameters = {1};
  SubsetManifold subset_a(3, constant_parameters);
  SubsetManifold subset_b(3, constant_parameters);
  ProductManifold<SubsetManifold, SubsetManifold> manifold(subset_a, subset_b);
  manifold.AmbientSize();
}

}  // namespace ceres
```