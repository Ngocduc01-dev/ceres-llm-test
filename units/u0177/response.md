**A. Test paths**

Constructor không có điểm rẽ nhánh nên chỉ có một đường đi duy nhất. Dòng `static_assert` được kiểm tra lúc biên dịch, không phải nhánh lúc chạy, và CFG không có node riêng cho nó. Mã nguồn khớp với CFG.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có đầu vào. `Size` là tham số template, phải khác `ceres::DYNAMIC` (giá trị hợp lệ: 1 đến 5) | `Size = 3` |

**C. Nhánh không test**

Không có nhánh nào cần bỏ qua. Unit không có điểm rẽ nhánh, nên không có nhánh `CHECK` và không có vòng lặp.

C2 dự kiến = 0 / 0 (tổng số nhánh là 0, nên coi như phủ đủ 100% khi node 1 được chạy qua)

**D. File test**

```cpp
// FILE: u0177_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(EuclideanManifoldConstructor, DefaultConstructorFixedSize) {
  ceres::EuclideanManifold<3> manifold;
  (void)manifold;
}
```