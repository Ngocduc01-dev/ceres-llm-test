# A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

# B. Bộ test case

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Giá trị hợp lệ theo chữ ký unit | Giá trị cố định |

# C. Nhánh không test

Không có nhánh không test; các nhánh khả thi được gọi qua các test ở trên.
C2 dự kiến = 0 / 0.

# D. File test

```cpp
// FILE: u0440_test.cc
#include "gtest/gtest.h"
#include "ceres/cubic_interpolation.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0440, PathP1) {
  const T * arg_0 = nullptr;
  const int arg_1 = 1;
  const int arg_2 = 1;
  ceres::Grid1D<int> target(arg_0, arg_1, arg_2);
  target.Grid1D<T, kDataDimension, kInterleaved>(nullptr, 1, 1);
}
```
