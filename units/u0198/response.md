**A. Test paths**

Unit không có điểm rẽ nhánh nào (0 điểm rẽ, 0 vòng lặp trong CFG). Vì vậy chỉ có 1 đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh nào (tuyến tính) |

Ghi chú: mã nguồn dòng 96–98 chỉ chuyển tiếp sang constructor private `ProductManifold(std::index_sequence<...>, Args&&...)`. Node 1 của CFG mô tả phần khởi tạo của constructor private đó. Hai bên khớp nhau, không có điểm khác biệt cần ghi chú thêm.

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có điều kiện ràng buộc. Hai manifold phải khớp kiểu mẫu `ProductManifold<EuclideanManifold<3>, SphereManifold<4>>`: `manifolds` gồm 1 `EuclideanManifold<3>` và 1 `SphereManifold<4>`. | `EuclideanManifold<3>()` và `SphereManifold<4>()` (kích thước cố định theo kiểu mẫu, không có giá trị ngẫu nhiên) |

**C. Nhánh không test**

Không có nhánh nào cần bỏ qua, vì unit không có điểm rẽ nhánh.
`C2 dự kiến = 0 / 0` (tổng số nhánh = 0, nên coi như phủ đủ 100%; dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0198_test.cc
#include "gtest/gtest.h"
#include "ceres/product_manifold.h"

namespace ceres {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ProductManifoldConstructorTest, TC1_EuclideanAndSphere) {
  ProductManifold<EuclideanManifold<3>, SphereManifold<4>> manifold(
      EuclideanManifold<3>(), SphereManifold<4>());
  (void)manifold;
}

}  // namespace ceres
```