**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → END | node 1: đúng (`manifold_ == nullptr`) |
| P2 | START → 1 → 2 → END | node 1: sai (`manifold_ != nullptr`) |

CFG khớp với mã nguồn. Hàm không có vòng lặp và không có `CHECK`.

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `size` từ 1 đến 5, không truyền manifold (`manifold_ == nullptr`) | `size = 3`, `index = 0`, mảng `{1.0, 2.0, 3.0}` |
| TC2 | P2 | `size` từ 1 đến 5, truyền manifold khác `nullptr` có `AmbientSize() == size`. Dùng `EuclideanManifold<3>` nên `size = 3` | `size = 3`, `index = 0`, mảng `{1.0, 2.0, 3.0}`, `EuclideanManifold<3>` |

**C. Nhánh không test**

Không có. Cả 2 nhánh của node 1 đều có test.

`C2 dự kiến = 2 / 2`

**D. File test**

```cpp
// FILE: u0482_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"
#include "ceres/parameter_block.h"

namespace ceres {
namespace internal {

// P1: START -> 1 (đúng: manifold_ == nullptr) -> 2 -> END
TEST(ParameterBlockTangentSizeTest, TC1_NoManifold) {
  double values[3] = {1.0, 2.0, 3.0};
  ParameterBlock block(values, 3, 0);
  block.TangentSize();
}

// P2: START -> 1 (sai: manifold_ != nullptr) -> 2 -> END
TEST(ParameterBlockTangentSizeTest, TC2_WithManifold) {
  double values[3] = {1.0, 2.0, 3.0};
  EuclideanManifold<3> manifold;
  ParameterBlock block(values, 3, 0, &manifold);
  block.TangentSize();
}

}  // namespace internal
}  // namespace ceres
```