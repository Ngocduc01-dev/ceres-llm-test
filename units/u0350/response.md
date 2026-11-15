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
// FILE: u0350_test.cc
#include "gtest/gtest.h"
#include "ceres/map_util.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0350, PathP1) {
  const typename Collection::value_type::first_type& arg_1{}
  const typename Collection::value_type::second_type& arg_2{}
  ceres::InsertIfNotPresent<double>(nullptr, arg_1, arg_2);
}
```
