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
// FILE: u0481_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0481, PathP1) {
  int arg_0 = 1;
  ceres::internal::ParameterBlock target(arg_0);
  target.LowerBound(1);
}

// Path P2: START -> 1 -> END.
TEST(Unit_u0481, PathP2) {
  int arg_0 = 1;
  ceres::internal::ParameterBlock target(arg_0);
  target.LowerBound(1);
}
```
