**A. Test paths**

Hàm có 0 điểm rẽ nhánh, không có vòng lặp và không có `CHECK`, nên chỉ có 1 đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `size` (số chiều, constructor `EuclideanManifold(int size)`): 1 đến 5. `x_ptr`: mảng `size` phần tử, giá trị tuỳ ý. `jacobian_ptr`: mảng `size*size` phần tử | `size = 3`, `x = {0.5, -1.2, 2.0}`, `jacobian` gồm 9 phần tử khởi tạo 0 |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh nên không có nhánh nào cần phủ, và cũng không có nhánh `CHECK`.

`C2 dự kiến = 0 / 0` (không có nhánh nào; toàn bộ câu lệnh của node 1 được chạy, tức là đạt C1 là 100%).

Ghi chú: CFG khớp với mã nguồn. Hàm này là `override` và dùng `size_` của object, nên tôi tạo object bằng `EuclideanManifold<DYNAMIC>(3)`, ứng với trường hợp `EuclideanManifold<-1>` của CFG.

**D. File test**

```cpp
// FILE: u0181_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(EuclideanManifoldPlusJacobian, TC1_P1_SinglePath) {
  ceres::EuclideanManifold<ceres::DYNAMIC> manifold(3);
  const double x[3] = {0.5, -1.2, 2.0};
  double jacobian[9] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  manifold.PlusJacobian(x, jacobian);
}
```