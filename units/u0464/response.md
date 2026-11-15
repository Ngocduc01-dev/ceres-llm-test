# Unit u0464
## A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → 4 → END | Theo CFG của prompt.md. |
| P2 | START → 1 → 2 → 3 → 4 → END | Theo CFG của prompt.md. |
| P3 | START → 1 → 2 → 3 → 4 → END | Theo CFG của prompt.md. |
| P4 | START → 1 → 2 → 3 → 4 → END | Theo CFG của prompt.md. |
| P5 | START → 1 → 2 → 3 → 4 → END | Theo CFG của prompt.md. |
| P6 | START → 1 → 2 → 3 → 4 → END | Theo CFG của prompt.md. |

## B. Bộ test case

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |
| TC2 | P2 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |
| TC3 | P3 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |
| TC4 | P4 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |
| TC5 | P5 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |
| TC6 | P6 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |

## C. Nhánh không test

Không ghi nhận nhánh không thể test từ CFG cung cấp.
C2 dự kiến = 2 / 2.

## D. File test

```cpp
// FILE: u0464_test.cc
#include "gtest/gtest.h"
#include "ceres/array_utils.h"

namespace ceres {
namespace internal {
// Path P1: START -> CFG nodes -> END.
TEST(MapValuesToContiguousRangeTest, ZeroIterations) {
  int array[1] = {7};
  MapValuesToContiguousRange(0, array);
}
// Path P1: START -> CFG nodes -> END.
TEST(MapValuesToContiguousRangeTest, OneIteration) {
  int array[1] = {3};
  MapValuesToContiguousRange(1, array);
}
// Path P1: START -> CFG nodes -> END.
TEST(MapValuesToContiguousRangeTest, TwoIterations) {
  int array[2] = {4, -2};
  MapValuesToContiguousRange(2, array);
}
// Path P1: START -> CFG nodes -> END.
TEST(MapValuesToContiguousRangeTest, ThreeIterations) {
  int array[3] = {2, 2, -1};
  MapValuesToContiguousRange(3, array);
}
// Path P1: START -> CFG nodes -> END.
TEST(MapValuesToContiguousRangeTest, FourIterations) {
  int array[4] = {5, 0, 5, -3};
  MapValuesToContiguousRange(4, array);
}
// Path P1: START -> CFG nodes -> END.
TEST(MapValuesToContiguousRangeTest, FiveIterations) {
  int array[5] = {1, -4, 1, 3, -4};
  MapValuesToContiguousRange(5, array);
}

}  // namespace internal
}  // namespace ceres
```
