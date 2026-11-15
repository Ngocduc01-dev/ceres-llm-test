**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm rẽ nhánh, không có vòng lặp, không có `CHECK`), nên chỉ có một test path. CFG khớp với mã nguồn.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `LineManifold<3>` có `size_ = 3`. `y` gồm 6 số thực, mỗi số trong [-5, 5]. `x` gồm 6 số thực, mỗi số trong [-5, 5], với `x_d` (3 phần tử sau) khác vectơ 0. `y_minus_x` là mảng 4 phần tử (2·(3−1)). | `y = {1.5, -2.0, 0.5, 3.0, 1.0, -1.5}`<br>`x = {0.5, 1.0, -1.0, 2.0, -3.0, 1.5}`<br>`y_minus_x = {0, 0, 0, 0}` |

**C. Nhánh không test**

Không có nhánh nào bị bỏ qua, vì hàm không có điểm rẽ nhánh.

`C2 dự kiến = 0 / 0` (không có nhánh nào cần phủ, coi như đạt 100%; dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0170_test.cc
#include "gtest/gtest.h"
#include "ceres/line_manifold.h"

// P1: START -> 1 -> END (hàm không có điểm rẽ nhánh)
TEST(LineManifoldMinusTest, TC1_P1_SinglePath) {
  ceres::LineManifold<3> manifold;

  const double y[6] = {1.5, -2.0, 0.5, 3.0, 1.0, -1.5};
  const double x[6] = {0.5, 1.0, -1.0, 2.0, -3.0, 1.5};
  double y_minus_x[4] = {0.0, 0.0, 0.0, 0.0};

  (void)manifold.Minus(y, x, y_minus_x);
}
```