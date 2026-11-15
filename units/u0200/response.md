**A. Test paths**

Hàm có 0 điểm rẽ nhánh nên chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh. Node 1: `return tangent_size_` |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Manifold thứ nhất: `size` 1–5, mask có ít nhất 1 phần tử `false`. Manifold thứ hai: `size` 1–5, mask có ít nhất 1 phần tử `false`. | Manifold thứ nhất: `size`=3, mask `{true,false,false}`. Manifold thứ hai: `size`=2, mask `{false,true}`. |

Hàm không có tham số. Giá trị trả về phụ thuộc vào kích thước của hai `SubsetManifold` dùng để dựng object.

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh và không có vòng lặp. Do tổng số nhánh bằng 0 nên C2 được coi là đạt trọn vẹn khi node 1 chạy qua.

`C2 dự kiến = 0 / 0 (không có nhánh nào; đường đi duy nhất P1 được chạy qua, coi như 100%)`

**D. File test**

```cpp
// FILE: u0200_test.cc
#include "gtest/gtest.h"
#include "ceres/product_manifold.h"

#include <vector>

namespace ceres {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ProductManifoldTangentSize, TC1_SinglePath) {
  ProductManifold<SubsetManifold, SubsetManifold> manifold(
      SubsetManifold(3, std::vector<bool>{true, false, false}),
      SubsetManifold(2, std::vector<bool>{false, true}));
  // Không kiểm tra giá trị trả về, chỉ gọi hàm một lần.
  manifold.TangentSize();
}

}  // namespace ceres
```