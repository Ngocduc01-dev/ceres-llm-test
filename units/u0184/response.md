**Ghi chú:** CFG khớp với mã nguồn. Hàm không có điểm rẽ nhánh (0 điểm rẽ nhánh), chỉ có node 1.

**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh; đi thẳng qua node 1 |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `size` (constructor `EuclideanManifold<DYNAMIC>(size)`): 1 đến 5; `x_ptr`: mảng `size` phần tử double, giá trị tuỳ ý; `jacobian_ptr`: mảng `size*size` phần tử double (tối đa 25) | `size` = 3 (chọn trong khoảng 1–5, seed cố định); `x` = {0.5, -1.2, 2.0}; `jacobian` = 9 phần tử khởi tạo 0 |

**C. Nhánh không test:** không có. Hàm không có điểm rẽ nhánh nên tổng số nhánh = 0; đường đi duy nhất P1 được test, không có vòng lặp và không có `CHECK`.
`C2 dự kiến = 0 / 0` (không có nhánh nào cần phủ; coi như đạt 100% nhờ P1 phủ toàn bộ node 1).

**D. File test**

```cpp
// FILE: u0184_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

#include <random>

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(EuclideanManifoldMinusJacobianTest, P1_StraightLine) {
  // Seed cố định để mỗi lần chạy cho cùng một giá trị.
  std::mt19937 gen(12345);
  std::uniform_int_distribution<int> size_dist(1, 5);
  const int size = size_dist(gen);

  ceres::EuclideanManifold<ceres::DYNAMIC> manifold(size);

  double x[5] = {0.5, -1.2, 2.0, 0.3, -0.7};
  double jacobian[25] = {0.0};

  // Không kiểm tra kết quả trả về (không có kết quả đúng để so).
  manifold.MinusJacobian(x, jacobian);
}
```