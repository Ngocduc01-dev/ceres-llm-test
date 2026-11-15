**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → 4 → END | node 1: đúng, node 3: đúng |
| P2 | START → 1 → 2 → 3 → 5 → END | node 1: đúng, node 3: sai |
| P3 | START → 1 → 6 → 7 → 8 → END | node 1: sai, node 7: đúng |
| P4 | START → 1 → 6 → 7 → 9 → END | node 1: sai, node 7: sai |

Hàm không có vòng lặp. CFG khớp với mã nguồn.

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | n lẻ, n ∈ {1,3,5}. j0 = k % n ≥ i0 = k / n. Với n=5: k ∈ {0,…,4, 6,7,8,9, 12,13,14} | n=5, k=2 (i0=0, j0=2) |
| TC2 | P2 | n lẻ. j0 < i0. Với n=5: k ∈ {5, 10, 11} | n=5, k=11 (i0=2, j0=1) |
| TC3 | P3 | n chẵn, n ∈ {2,4}. j0 = k % (n+1) > i0 = k / (n+1). Với n=4: k ∈ {1,2,3,4, 7,8,9} | n=4, k=2 (i0=0, j0=2) |
| TC4 | P4 | n chẵn. j0 ≤ i0. Với n=4: k ∈ {0, 5, 6} | n=4, k=6 (i0=1, j0=1) |

**C. Nhánh không test**

Không có. Cả 6 nhánh đều có test đi qua.

`C2 dự kiến = 6 / 6`

**D. File test**

```cpp
// FILE: u0529_test.cc
#include "gtest/gtest.h"
#include "ceres/parallel_utils.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> 2 -> 3 -> 4 -> END (node 1: đúng, node 3: đúng)
TEST(LinearIndexToUpperTriangularIndexTest, OddNJ0GreaterOrEqualI0) {
  int i = 0;
  int j = 0;
  LinearIndexToUpperTriangularIndex(2, 5, &i, &j);
}

// P2: START -> 1 -> 2 -> 3 -> 5 -> END (node 1: đúng, node 3: sai)
TEST(LinearIndexToUpperTriangularIndexTest, OddNJ0LessThanI0) {
  int i = 0;
  int j = 0;
  LinearIndexToUpperTriangularIndex(11, 5, &i, &j);
}

// P3: START -> 1 -> 6 -> 7 -> 8 -> END (node 1: sai, node 7: đúng)
TEST(LinearIndexToUpperTriangularIndexTest, EvenNJ0GreaterThanI0) {
  int i = 0;
  int j = 0;
  LinearIndexToUpperTriangularIndex(2, 4, &i, &j);
}

// P4: START -> 1 -> 6 -> 7 -> 9 -> END (node 1: sai, node 7: sai)
TEST(LinearIndexToUpperTriangularIndexTest, EvenNJ0LessOrEqualI0) {
  int i = 0;
  int j = 0;
  LinearIndexToUpperTriangularIndex(6, 4, &i, &j);
}

}  // namespace internal
}  // namespace ceres
```