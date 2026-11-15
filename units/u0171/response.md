**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `LineManifold<3>` (size_ = 3). `x_ptr` gồm 6 số: 3 số đầu là điểm gốc, thuộc [-1, 1]. 3 số sau là hướng, khác vector 0 và chuẩn hoá (norm = 1). `jacobian_ptr` trỏ tới vùng nhớ 4×6 = 24 double. | `x = {0.3, -0.7, 0.5, 0.48, 0.64, 0.6}`, `jacobian` gồm 24 số 0.0 |

Mảng `x` và `jacobian` vượt giới hạn 5 phần tử của mục 4, vì kích thước do hàm yêu cầu (6 và 24 phần tử) nên không thể rút gọn.

**C. Nhánh không test**

Không có nhánh nào bị bỏ. Hàm không có điểm rẽ nhánh, `CHECK` hay vòng lặp.

`C2 dự kiến = 0 / 0` (tổng số nhánh bằng 0, nên coi như đạt 100%; mọi câu lệnh ở node 1 đều được chạy bởi TC1).

**D. File test**

```cpp
// FILE: u0171_test.cc
#include "gtest/gtest.h"
#include "ceres/line_manifold.h"

// P1: START -> 1 -> END (hàm không có điểm rẽ nhánh)
TEST(LineManifoldMinusJacobian, StraightLinePath) {
  ceres::LineManifold<3> manifold;
  double x[6] = {0.3, -0.7, 0.5, 0.48, 0.64, 0.6};
  double jacobian[24] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                         0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                         0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  manifold.MinusJacobian(x, jacobian);
}
```