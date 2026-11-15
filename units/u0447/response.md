# Unit u0447
## A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → END | Theo CFG của prompt.md. |
| P2 | START → 1 → 2 → 3 → END | Theo CFG của prompt.md. |

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
// FILE: u0447_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/autodiff.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0447, PathP1) {
  int arg_0 = 1;
  JetT* arg_1 = nullptr;
  T** arg_2 = nullptr;
  ceres::Take1stOrderParts<integer_sequence<int, 2, 2>>::Apply<Jet<double, 4>, double> target(arg_0, arg_1, arg_2);
  target.Apply(1, nullptr, nullptr);
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0447, PathP2) {
  int arg_0 = 1;
  JetT* arg_1 = nullptr;
  T** arg_2 = nullptr;
  ceres::Take1stOrderParts<integer_sequence<int, 2, 2>>::Apply<Jet<double, 4>, double> target(arg_0, arg_1, arg_2);
  target.Apply(1, nullptr, nullptr);
}
```
