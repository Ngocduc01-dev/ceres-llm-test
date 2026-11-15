# Unit u0479
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
// FILE: u0479_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0479, PathP1) {
  double * arg_0 = nullptr;
  ceres::internal::ParameterBlock target(arg_0);
  target.GetState(nullptr);
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0479, PathP2) {
  double * arg_0 = nullptr;
  ceres::internal::ParameterBlock target(arg_0);
  target.GetState(nullptr);
}
```
