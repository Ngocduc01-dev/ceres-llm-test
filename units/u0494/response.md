**Ghi chú:** CFG khớp với mã nguồn. Có 2 điểm rẽ nhánh (node 2 và node 4), tổng cộng 4 nhánh. Dòng `if` ở node 2 và node 4 không nằm trong vòng lặp nên không có yêu cầu về số lần lặp.

**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → 4 → 5 → END | node 2: đúng, node 4: đúng |
| P2 | START → 1 → 2 → 4 → END | node 2: sai, node 4: sai |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f != nullptr`, `dfdx != nullptr`; p0..p3 và x là số thực bất kỳ (chọn trong [-5, 5]) | p0=1.3, p1=-2.1, p2=0.7, p3=3.4, x=0.6 (seed cố định 0, giá trị chọn sẵn); f, dfdx trỏ tới biến double hợp lệ |
| TC2 | P2 | `f == nullptr`, `dfdx == nullptr`; p0..p3 và x bất kỳ trong [-5, 5] | p0=-4.2, p1=2.5, p2=1.1, p3=-0.9, x=0.25; f = dfdx = nullptr |

**C. Nhánh không test**

Không có. Mọi nhánh đều đạt được và không có `CHECK` trong hàm.

`C2 dự kiến = 4 / 4` (dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0494_test.cc
#include "gtest/gtest.h"
#include "ceres/cubic_interpolation.h"

// P1: node 2: đúng, node 4: đúng
TEST(CubicHermiteSplineTest, BothOutputsNonNull) {
  Eigen::Matrix<double, 1, 1> p0;
  Eigen::Matrix<double, 1, 1> p1;
  Eigen::Matrix<double, 1, 1> p2;
  Eigen::Matrix<double, 1, 1> p3;
  p0 << 1.3;
  p1 << -2.1;
  p2 << 0.7;
  p3 << 3.4;
  const double x = 0.6;
  double f = 0.0;
  double dfdx = 0.0;
  ceres::CubicHermiteSpline<1>(p0, p1, p2, p3, x, &f, &dfdx);
}

// P2: node 2: sai, node 4: sai
TEST(CubicHermiteSplineTest, BothOutputsNull) {
  Eigen::Matrix<double, 1, 1> p0;
  Eigen::Matrix<double, 1, 1> p1;
  Eigen::Matrix<double, 1, 1> p2;
  Eigen::Matrix<double, 1, 1> p3;
  p0 << -4.2;
  p1 << 2.5;
  p2 << 1.1;
  p3 << -0.9;
  const double x = 0.25;
  ceres::CubicHermiteSpline<1>(p0, p1, p2, p3, x, nullptr, nullptr);
}
```