# A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | node 1: đúng/sai theo dữ liệu |
| P2 | START → 1 → END | node 1: đúng/sai theo dữ liệu |

# B. Bộ test case

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Giá trị hợp lệ theo chữ ký unit | Giá trị cố định |
| TC2 | P2 | Giá trị hợp lệ theo chữ ký unit | Giá trị cố định |

# C. Nhánh không test

Không có nhánh không test; các nhánh khả thi được gọi qua các test ở trên.
C2 dự kiến = 4 / 4.

# D. File test

```cpp
// FILE: u0442_test.cc
#include "gtest/gtest.h"
#include "ceres/cubic_interpolation.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0442, PathP1) {
  const JetT& arg_0{}
  const JetT& arg_1{}
  const JetT& arg_0{};
  const JetT& arg_1{};
  JetT* arg_2 = nullptr;
  ceres::BiCubicInterpolator<Grid2D<double, 2>>::Evaluate<Jet<double, 4>> target(arg_0, arg_1, arg_2);
  target.Evaluate(arg_0, arg_1, nullptr);
}

// Path P2: START -> 1 -> END.
TEST(Unit_u0442, PathP2) {
  const JetT& arg_0{}
  const JetT& arg_1{}
  const JetT& arg_0{};
  const JetT& arg_1{};
  JetT* arg_2 = nullptr;
  ceres::BiCubicInterpolator<Grid2D<double, 2>>::Evaluate<Jet<double, 4>> target(arg_0, arg_1, arg_2);
  target.Evaluate(arg_0, arg_1, nullptr);
}
```
