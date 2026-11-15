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
// FILE: u0352_test.cc
#include "gtest/gtest.h"
#include "ceres/pair_hash.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0352, PathP1) {
  uint32_t & arg_0{}
  uint32_t & arg_1{}
  uint32_t & arg_2{}
  ceres::internal::hash_mix(arg_0, arg_1, arg_2);
}
```
