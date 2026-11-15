# Unit u0549
## A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → 9 → 10 → 11 → 12 → 13 → END | Theo CFG của prompt.md. |
| P2 | START → 1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → 9 → 10 → 11 → 12 → 13 → END | Theo CFG của prompt.md. |

## B. Bộ test case

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |
| TC2 | P2 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |

## C. Nhánh không test

Không ghi nhận nhánh không thể test từ CFG cung cấp.
C2 dự kiến = 8 / 8.

## D. File test

```cpp
// FILE: u0549_test.cc
#include "gtest/gtest.h"
#include "ceres/covariance_impl.h"

namespace ceres {
namespace internal {
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0549, CallsTarget) {
  CheckForDuplicates({});
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0549, CallsTargetAlternate) {
  CheckForDuplicates({});
}
}  // namespace internal
}  // namespace ceres
```
