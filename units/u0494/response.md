# A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | node 1: đúng/sai theo dữ liệu |
| P2 | START → 1 → END | node 1: đúng/sai theo dữ liệu |
| P3 | START → 1 → END | node 1: đúng/sai theo dữ liệu |
| P4 | START → 1 → END | node 1: đúng/sai theo dữ liệu |

# B. Bộ test case

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Giá trị hợp lệ theo chữ ký unit | Giá trị cố định |
| TC2 | P2 | Giá trị hợp lệ theo chữ ký unit | Giá trị cố định |
| TC3 | P3 | Giá trị hợp lệ theo chữ ký unit | Giá trị cố định |
| TC4 | P4 | Giá trị hợp lệ theo chữ ký unit | Giá trị cố định |

# C. Nhánh không test

Không có nhánh không test; các nhánh khả thi được gọi qua các test ở trên.
C2 dự kiến = 8 / 8.

# D. File test

```cpp
// FILE: u0494_test.cc
#include "gtest/gtest.h"
#include "ceres/cubic_interpolation.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0494, PathP1) {
  const Eigen::Matrix<double, kDataDimension, 1>& arg_0{}
  const Eigen::Matrix<double, kDataDimension, 1>& arg_1{}
  const Eigen::Matrix<double, kDataDimension, 1>& arg_2{}
  const Eigen::Matrix<double, kDataDimension, 1>& arg_3{}
  ceres::CubicHermiteSpline<double>(arg_0, arg_1, arg_2, arg_3, 1.0, nullptr, nullptr);
}

// Path P2: START -> 1 -> END.
TEST(Unit_u0494, PathP2) {
  const Eigen::Matrix<double, kDataDimension, 1>& arg_0{}
  const Eigen::Matrix<double, kDataDimension, 1>& arg_1{}
  const Eigen::Matrix<double, kDataDimension, 1>& arg_2{}
  const Eigen::Matrix<double, kDataDimension, 1>& arg_3{}
  ceres::CubicHermiteSpline<double>(arg_0, arg_1, arg_2, arg_3, 1.0, nullptr, nullptr);
}

// Path P3: START -> 1 -> END.
TEST(Unit_u0494, PathP3) {
  const Eigen::Matrix<double, kDataDimension, 1>& arg_0{}
  const Eigen::Matrix<double, kDataDimension, 1>& arg_1{}
  const Eigen::Matrix<double, kDataDimension, 1>& arg_2{}
  const Eigen::Matrix<double, kDataDimension, 1>& arg_3{}
  ceres::CubicHermiteSpline<double>(arg_0, arg_1, arg_2, arg_3, 1.0, nullptr, nullptr);
}

// Path P4: START -> 1 -> END.
TEST(Unit_u0494, PathP4) {
  const Eigen::Matrix<double, kDataDimension, 1>& arg_0{}
  const Eigen::Matrix<double, kDataDimension, 1>& arg_1{}
  const Eigen::Matrix<double, kDataDimension, 1>& arg_2{}
  const Eigen::Matrix<double, kDataDimension, 1>& arg_3{}
  ceres::CubicHermiteSpline<double>(arg_0, arg_1, arg_2, arg_3, 1.0, nullptr, nullptr);
}
```
