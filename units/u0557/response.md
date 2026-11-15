# Unit u0557
## A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → 9 → 10 → 11 → 12 → 13 → 14 → 15 → 16 → 17 → 18 → 19 → 20 → 21 → 22 → 23 → END | Theo CFG của prompt.md. |
| P2 | START → 1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → 9 → 10 → 11 → 12 → 13 → 14 → 15 → 16 → 17 → 18 → 19 → 20 → 21 → 22 → 23 → END | Theo CFG của prompt.md. |

## B. Bộ test case

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |
| TC2 | P2 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |

## C. Nhánh không test

Không ghi nhận nhánh không thể test từ CFG cung cấp.
C2 dự kiến = 12 / 12.

## D. File test

```cpp
// FILE: u0557_test.cc
#include "gtest/gtest.h"
#include "ceres/graph.h"
#include "ceres/graph_algorithms.h"

namespace ceres {
namespace internal {
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0557, CallsTarget) {
  double ordering_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  IndependentSetOrdering({}, ordering_data);
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0557, CallsTargetAlternate) {
  double ordering_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  IndependentSetOrdering({}, ordering_data);
}
}  // namespace internal
}  // namespace ceres
```
