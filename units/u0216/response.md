**A. Test paths**

Unit không có điểm rẽ nhánh và không có vòng lặp. CFG khớp với mã nguồn (chỉ có node 1) nên chỉ có một đường đi.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh, chỉ có một đường duy nhất |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `SphereManifold<2>` (size = 2). `x_ptr`, `y_ptr`: mảng 2 phần tử, mỗi phần tử trong [-1, 1], `x` khác vectơ không. `y_minus_x_ptr`: mảng 1 phần tử (size − 1). | `x = {0.6, 0.8}`, `y = {-0.28, 0.96}`, `y_minus_x = {0.0}` |

**C. Nhánh không test**

- Không có nhánh nào bị bỏ. Hàm không có `CHECK` hay vòng lặp, nên không cần test số lần lặp.
- C2 dự kiến = 0 / 0 (không có nhánh nào, nên mọi nhánh đều được phủ, coi như 100%). Đây là kết quả dự kiến, chưa chạy thật.

**D. File test**

```cpp
// FILE: u0216_test.cc
#include "gtest/gtest.h"
#include "ceres/sphere_manifold.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(SphereManifoldMinusTest, TC1_P1_StaticSize2) {
  ceres::SphereManifold<2> manifold;
  const double x[2] = {0.6, 0.8};
  const double y[2] = {-0.28, 0.96};
  double y_minus_x[1] = {0.0};
  manifold.Minus(y, x, y_minus_x);
}
```