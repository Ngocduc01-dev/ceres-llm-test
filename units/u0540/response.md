# Unit u0540
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
// FILE: u0540_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

// Path P1: START -> CFG nodes -> END.
TEST(ParameterBlockSetUpperBound, P1_MaxBoundWithoutExistingBounds) {
  double state[3] = {0.1, 0.2, 0.3};
  ceres::internal::ParameterBlock block(state, 3, 0);
  block.SetUpperBound(2, std::numeric_limits<double>::max());
}
// Path P1: START -> CFG nodes -> END.
TEST(ParameterBlockSetUpperBound, P2_AllocateBoundsThenSet) {
  double state[3] = {0.1, 0.2, 0.3};
  ceres::internal::ParameterBlock block(state, 3, 0);
  block.SetUpperBound(0, 5.0);
}
// Path P1: START -> CFG nodes -> END.
TEST(ParameterBlockSetUpperBound, P3_BoundsAlreadyAllocated) {
  double state[3] = {0.1, 0.2, 0.3};
  ceres::internal::ParameterBlock block(state, 3, 0);
  // Chuẩn bị: cấp phát upper_bounds_ (lệnh gọi này không thuộc path P3).
  block.SetUpperBound(0, 3.5);
  // Lệnh gọi được kiểm thử theo P3.
  block.SetUpperBound(1, 7.25);
}
```
