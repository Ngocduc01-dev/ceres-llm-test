**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → END | node 2: đúng |
| P2 | START → 1 → 2 → 4 → END | node 2: sai |

Node 2 là điểm rẽ nhánh duy nhất, và hàm không có vòng lặp. Node 1 chỉ là khối lệnh gán nên không tính nhánh.

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `delta` (3 phần tử) có `norm_delta == 0`, tức `delta = {0,0,0}`. `x` (4 phần tử) tuỳ ý trong [-1, 1]. | `x = {0.5, 0.5, 0.5, 0.5}`, `delta = {0, 0, 0}` |
| TC2 | P2 | `delta` có `norm_delta != 0`, tức ít nhất một phần tử khác 0, mỗi phần tử trong [-1, 1]. `x` khác vector 0, trong [-1, 1]. | `x = {0.5, 0.5, 0.5, 0.5}`, `delta = {0.3, -0.2, 0.5}` |

Giá trị trong bảng đã được chọn cố định, nên mỗi lần chạy cho cùng kết quả.

**C. Nhánh không test**

Không có. Cả hai nhánh của node 2 đều đi tới được, và hàm không có `CHECK`.

C2 dự kiến = 2 / 2

**D. File test**

```cpp
// FILE: u0463_test.cc
#include "gtest/gtest.h"
#include "ceres/sphere_manifold.h"

// Path P1: START -> 1 -> 2 (đúng) -> 3 -> END
TEST(SphereManifoldPlusTest, TC1_ZeroDelta) {
  ceres::SphereManifold<4> manifold;
  const double x[4] = {0.5, 0.5, 0.5, 0.5};
  const double delta[3] = {0.0, 0.0, 0.0};
  double x_plus_delta[4] = {0.0, 0.0, 0.0, 0.0};
  manifold.Plus(x, delta, x_plus_delta);
}

// Path P2: START -> 1 -> 2 (sai) -> 4 -> END
TEST(SphereManifoldPlusTest, TC2_NonZeroDelta) {
  ceres::SphereManifold<4> manifold;
  const double x[4] = {0.5, 0.5, 0.5, 0.5};
  const double delta[3] = {0.3, -0.2, 0.5};
  double x_plus_delta[4] = {0.0, 0.0, 0.0, 0.0};
  manifold.Plus(x, delta, x_plus_delta);
}
```