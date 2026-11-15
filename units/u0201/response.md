**A. Test paths**

Hàm có 0 điểm rẽ nhánh, nên chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh. Node 1 gọi `PlusImpl` rồi trả về. |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Object là `ProductManifold<SubsetManifold ×4>`, mỗi manifold con có kích thước 1 và không có tham số cố định (`{false}`). Vì vậy `x`, `delta`, `x_plus_delta` đều có 4 phần tử. Giá trị của `x` và `delta` nằm trong [-2, 2]. | `x = {0.3, -1.2, 0.7, 1.1}`, `delta = {0.5, 0.1, -0.4, 0.9}`, `x_plus_delta = {0, 0, 0, 0}` (giá trị cố định, không dùng sinh số ngẫu nhiên) |

**C. Nhánh không test**

Không có nhánh nào bị bỏ. Hàm không có điểm rẽ nhánh và không có `CHECK` trong phần thân.
`C2 dự kiến = 0 / 0` (không có nhánh nào để phủ, coi như đạt 100%; node 1 được chạy bởi TC1).

**D. File test**

```cpp
// FILE: u0201_test.cc
#include "gtest/gtest.h"
#include "ceres/product_manifold.h"

#include <vector>

namespace ceres {
namespace {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ProductManifoldPlusTest, TC1_SinglePath) {
  ProductManifold<SubsetManifold,
                  SubsetManifold,
                  SubsetManifold,
                  SubsetManifold>
      manifold(SubsetManifold(1, std::vector<bool>{false}),
               SubsetManifold(1, std::vector<bool>{false}),
               SubsetManifold(1, std::vector<bool>{false}),
               SubsetManifold(1, std::vector<bool>{false}));

  const double x[4] = {0.3, -1.2, 0.7, 1.1};
  const double delta[4] = {0.5, 0.1, -0.4, 0.9};
  double x_plus_delta[4] = {0.0, 0.0, 0.0, 0.0};

  manifold.Plus(x, delta, x_plus_delta);
}

}  // namespace
}  // namespace ceres
```