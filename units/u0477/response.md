# Unit u0477
## A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → END | Theo CFG của prompt.md. |
| P2 | START → 1 → 2 → END | Theo CFG của prompt.md. |

## B. Bộ test case

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |
| TC2 | P2 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |

## C. Nhánh không test

Không ghi nhận nhánh không thể test từ CFG cung cấp.
C2 dự kiến = 2 / 2.

## D. File test

```cpp
// FILE: u0477_test.cc
#include "gtest/gtest.h"
#include "ceres/parallel_for.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0477, PathP1) {
  std::mutex & arg_1{}
  ceres::internal::MakeConditionalLock(1, arg_1);
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0477, PathP2) {
  std::mutex & arg_1{}
  ceres::internal::MakeConditionalLock(1, arg_1);
}
```
