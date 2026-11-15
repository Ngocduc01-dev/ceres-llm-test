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
// FILE: u0445_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/array_selector.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0445, PathP1) {
  int arg_0 = 1;
  ceres::ArraySelector<int, -1, 20> target(arg_0);
  target.ArraySelector<type-parameter-0-0, num_elements, max_num_elements_on_stack, false, true>(1);
}
```
