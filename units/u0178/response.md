**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh; node 1: `return size_` |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `size` (tham số constructor) từ 1 đến 5 (hàm không có tham số; không có điều kiện đường đi) | `size = 3` (chọn cố định, đại diện cho khoảng) |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh nào (0 nhánh), không có vòng lặp, không có `CHECK`. Một test đi hết đường đi duy nhất.

`C2 dự kiến = 0 / 0` (không có nhánh nào; mọi câu lệnh đều được chạy, tức 100% C1).

**D. File test**

```cpp
// FILE: u0178_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(EuclideanManifoldAmbientSizeTest, P1_ReturnSize) {
  ceres::EuclideanManifold<ceres::DYNAMIC> manifold(3);
  manifold.AmbientSize();
}
```