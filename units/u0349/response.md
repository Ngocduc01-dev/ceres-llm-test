**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm rẽ nhánh), nên chỉ có một test path duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh; node 1 chạy tuần tự rồi `return true` |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `x`: mảng 4 double (quaternion), không có điều kiện ràng buộc từ đường đi; chọn trong [-1, 1]. `jacobian`: mảng 12 double (ma trận 4×3), giá trị ban đầu bất kỳ | `x = {0.18, -0.42, 0.67, 0.58}` (sinh bằng seed cố định, không dùng RNG trong code); `jacobian` khởi tạo 0 |

**C. Nhánh không test**

Không có nhánh nào bị bỏ (hàm không có điểm rẽ nhánh, không có `CHECK`).

`C2 dự kiến = 0 / 0` (không có nhánh; mọi câu lệnh của node 1 đều được chạy, tương đương 100%).

**D. File test**

```cpp
// FILE: u0349_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(EigenQuaternionManifoldMinusJacobian, P1_TuanTu) {
  ceres::EigenQuaternionManifold manifold;
  double x[4] = {0.18, -0.42, 0.67, 0.58};
  double jacobian[12] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                         0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  manifold.MinusJacobian(x, jacobian);
}
```