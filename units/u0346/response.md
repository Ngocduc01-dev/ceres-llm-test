**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh (đường đi duy nhất) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `x`: 4 số thực (quaternion theo thứ tự Eigen: x, y, z, w), mỗi số trong [-1, 1]; `delta`: 3 số thực trong [-1, 1]; `x_plus_delta`: mảng 4 số thực để ghi kết quả | `x = {0.1, 0.2, 0.3, 0.9}`, `delta = {0.05, -0.1, 0.2}`, `x_plus_delta = {0, 0, 0, 0}` |

(Không có điều kiện đường đi và không có vòng lặp. Giá trị được chọn cố định, không dùng sinh số ngẫu nhiên.)

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh nên tổng số nhánh là 0 và không có `CHECK` trong unit. CFG khớp với mã nguồn (dòng 293–294).

`C2 dự kiến = 0 / 0` (không có nhánh nào; một test chạy qua toàn bộ node 1 → END nên đạt 100% độ phủ câu lệnh của hàm).

**D. File test**

```cpp
// FILE: u0346_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(EigenQuaternionManifoldPlus, TC1_SinglePath) {
  ceres::EigenQuaternionManifold manifold;
  const double x[4] = {0.1, 0.2, 0.3, 0.9};
  const double delta[3] = {0.05, -0.1, 0.2};
  double x_plus_delta[4] = {0.0, 0.0, 0.0, 0.0};
  manifold.Plus(x, delta, x_plus_delta);
}
```