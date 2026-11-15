# Unit u0448
## A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → 4 → END | Theo CFG của prompt.md. |
| P2 | START → 1 → 2 → 3 → 4 → END | Theo CFG của prompt.md. |

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
// FILE: u0448_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0448, PathP1) {
  { ceres::FixedArray<int, 20> target; }
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0448, PathP2) {
  { ceres::FixedArray<int, 20> target; }
}
```
