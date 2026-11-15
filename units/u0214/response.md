**Ghi chú:** Hàm không có điểm rẽ nhánh nào (0 điểm rẽ nhánh). `static_assert` được kiểm tra lúc biên dịch, không phải nhánh chạy. CFG khớp với mã nguồn. Chỉ có một đường đi duy nhất.

**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có tham số đầu vào. Tham số template `AmbientSpaceDimension` phải khác `Eigen::Dynamic` (≥ 1) | `AmbientSpaceDimension = 4` (khớp CFG `SphereManifold<4>`) |

**C. Nhánh không test:** Không có. Tổng số nhánh = 0, không có nhánh nào bị bỏ qua. Nhánh `static_assert` sai sẽ gây lỗi biên dịch, không phải nhánh chạy, nên không test.

`C2 dự kiến = 0 / 0` (không có điểm rẽ nhánh; đường đi duy nhất P1 được TC1 chạy qua, coi như 100%).

**D. File test**

```cpp
// FILE: u0214_test.cc
#include "gtest/gtest.h"
#include "ceres/sphere_manifold.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(SphereManifoldConstructorTest, DefaultConstructorStaticSize4) {
  SphereManifold<4> manifold;
  (void)manifold;
}

}  // namespace internal
}  // namespace ceres
```