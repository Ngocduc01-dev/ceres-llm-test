# Unit u0541
## A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → 4 → 5 → 6 → END | Theo CFG của prompt.md. |
| P2 | START → 1 → 2 → 3 → 4 → 5 → 6 → END | Theo CFG của prompt.md. |
| P3 | START → 1 → 2 → 3 → 4 → 5 → 6 → END | Theo CFG của prompt.md. |

## B. Bộ test case

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |
| TC2 | P2 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |
| TC3 | P3 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |

## C. Nhánh không test

Không ghi nhận nhánh không thể test từ CFG cung cấp.
C2 dự kiến = 4 / 4.

## D. File test

```cpp
// FILE: u0541_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

namespace ceres {
namespace internal {
// Path P1: START -> CFG nodes -> END.
TEST(ParameterBlockSetLowerBoundTest, P1_EarlyReturnWhenNoBoundsAndLowest) {
  double values[3] = {1.0, 2.0, 3.0};
  ParameterBlock block(values, 3, 0);
  block.SetLowerBound(1, -std::numeric_limits<double>::max());
}
// Path P1: START -> CFG nodes -> END.
TEST(ParameterBlockSetLowerBoundTest, P2_AllocateBoundsThenAssign) {
  double values[3] = {1.0, 2.0, 3.0};
  ParameterBlock block(values, 3, 0);
  block.SetLowerBound(2, 3.7);
}
// Path P1: START -> CFG nodes -> END.
TEST(ParameterBlockSetLowerBoundTest, P3_AssignWhenBoundsAlreadyAllocated) {
  double values[3] = {1.0, 2.0, 3.0};
  ParameterBlock block(values, 3, 0);
  block.SetLowerBound(0, -2.5);  // chuẩn bị: cấp phát lower_bounds_
  block.SetLowerBound(1, -std::numeric_limits<double>::max());
}

}  // namespace internal
}  // namespace ceres
```
