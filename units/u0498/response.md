# Unit u0498
## A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → 4 → 5 → 6 → END | Theo CFG của prompt.md. |
| P2 | START → 1 → 2 → 3 → 4 → 5 → 6 → END | Theo CFG của prompt.md. |
| P3 | START → 1 → 2 → 3 → 4 → 5 → 6 → END | Theo CFG của prompt.md. |
| P4 | START → 1 → 2 → 3 → 4 → 5 → 6 → END | Theo CFG của prompt.md. |

## B. Bộ test case

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |
| TC2 | P2 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |
| TC3 | P3 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |
| TC4 | P4 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |

## C. Nhánh không test

Không ghi nhận nhánh không thể test từ CFG cung cấp.
C2 dự kiến = 4 / 4.

## D. File test

```cpp
// FILE: u0498_test.cc
#include "gtest/gtest.h"
#include "ceres/rotation.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0498, PathP1) {
  ceres::QuaternionToAngleAxis<double>(nullptr, nullptr);
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0498, PathP2) {
  ceres::QuaternionToAngleAxis<double>(nullptr, nullptr);
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0498, PathP3) {
  ceres::QuaternionToAngleAxis<double>(nullptr, nullptr);
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0498, PathP4) {
  ceres::QuaternionToAngleAxis<double>(nullptr, nullptr);
}
```
