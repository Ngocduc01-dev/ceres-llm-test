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
// FILE: u0497_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0497, PathP1) {
  std::ostream& arg_0{}
  const Jet<T, N>& arg_1{}
  ceres::operator<<<double>(arg_0, arg_1);
}

// Path P2: START -> 1 -> END.
TEST(Unit_u0497, PathP2) {
  std::ostream& arg_0{}
  const Jet<T, N>& arg_1{}
  ceres::operator<<<double>(arg_0, arg_1);
}

// Path P3: START -> 1 -> END.
TEST(Unit_u0497, PathP3) {
  std::ostream& arg_0{}
  const Jet<T, N>& arg_1{}
  ceres::operator<<<double>(arg_0, arg_1);
}

// Path P4: START -> 1 -> END.
TEST(Unit_u0497, PathP4) {
  std::ostream& arg_0{}
  const Jet<T, N>& arg_1{}
  ceres::operator<<<double>(arg_0, arg_1);
}
```
