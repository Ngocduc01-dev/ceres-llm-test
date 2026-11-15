**A. Test paths**

Hàm có 0 điểm rẽ nhánh nên chỉ có một đường đi duy nhất. CFG khớp với mã nguồn.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào (đường đi tuyến tính) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `LineManifold<3>` có size_ = 3. `x_ptr` là mảng 6 phần tử: 3 phần tử đầu là điểm gốc o (tùy ý), 3 phần tử sau là hướng d (khác vector 0, mỗi phần tử trong [0.5, 2.0]). `jacobian_ptr` là mảng 24 phần tử (6×4) | x = {0.7, 1.3, 0.9, 1.2, 0.6, 1.8}; jacobian = 24 số 0.0 |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh và không có `CHECK`.

`C2 dự kiến = 0 / 0 (không có nhánh nào cần phủ; TC1 chạy qua toàn bộ node 1 nên đạt 100% câu lệnh)`

**D. File test**

```cpp
// FILE: u0169_test.cc
#include "gtest/gtest.h"
#include "ceres/line_manifold.h"

// TC1 - P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(LineManifoldPlusJacobian, P1_LinearPath) {
  ceres::LineManifold<3> manifold;
  const double x[6] = {0.7, 1.3, 0.9, 1.2, 0.6, 1.8};
  double jacobian[24] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                         0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                         0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  manifold.PlusJacobian(x, jacobian);
}
```