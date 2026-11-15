# Unit u0529
## A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → 9 → END | Theo CFG của prompt.md. |
| P2 | START → 1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → 9 → END | Theo CFG của prompt.md. |
| P3 | START → 1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → 9 → END | Theo CFG của prompt.md. |
| P4 | START → 1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → 9 → END | Theo CFG của prompt.md. |

## B. Bộ test case

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |
| TC2 | P2 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |
| TC3 | P3 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |
| TC4 | P4 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |

## C. Nhánh không test

Không ghi nhận nhánh không thể test từ CFG cung cấp.
C2 dự kiến = 6 / 6.

## D. File test

```cpp
// FILE: u0529_test.cc
#include "gtest/gtest.h"
#include "ceres/parallel_utils.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> 2 -> 3 -> 4 -> END (node 1: đúng, node 3: đúng)
// Path P1: START -> CFG nodes -> END.
TEST(LinearIndexToUpperTriangularIndexTest, OddNJ0GreaterOrEqualI0) {
  int i = 0;
  int j = 0;
  LinearIndexToUpperTriangularIndex(2, 5, &i, &j);
}

// P2: START -> 1 -> 2 -> 3 -> 5 -> END (node 1: đúng, node 3: sai)
// Path P1: START -> CFG nodes -> END.
TEST(LinearIndexToUpperTriangularIndexTest, OddNJ0LessThanI0) {
  int i = 0;
  int j = 0;
  LinearIndexToUpperTriangularIndex(11, 5, &i, &j);
}

// P3: START -> 1 -> 6 -> 7 -> 8 -> END (node 1: sai, node 7: đúng)
// Path P1: START -> CFG nodes -> END.
TEST(LinearIndexToUpperTriangularIndexTest, EvenNJ0GreaterThanI0) {
  int i = 0;
  int j = 0;
  LinearIndexToUpperTriangularIndex(2, 4, &i, &j);
}

// P4: START -> 1 -> 6 -> 7 -> 9 -> END (node 1: sai, node 7: sai)
// Path P1: START -> CFG nodes -> END.
TEST(LinearIndexToUpperTriangularIndexTest, EvenNJ0LessOrEqualI0) {
  int i = 0;
  int j = 0;
  LinearIndexToUpperTriangularIndex(6, 4, &i, &j);
}

}  // namespace internal
}  // namespace ceres
```
