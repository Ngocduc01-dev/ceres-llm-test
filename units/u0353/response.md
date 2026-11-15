# Unit u0353
## A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh. |

## B. Bộ test case

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |

## C. Nhánh không test

Không có nhánh điều khiển trong CFG.
C2 dự kiến = 0 / 0.

## D. File test

```cpp
// FILE: u0353_test.cc
#include "gtest/gtest.h"
#include "ceres/pair_hash.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0353, PathP1) {
  uint64_t & arg_0{}
  uint64_t & arg_1{}
  uint64_t & arg_2{}
  ceres::internal::hash_mix(arg_0, arg_1, arg_2);
}
```
