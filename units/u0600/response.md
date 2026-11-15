# Unit u0600
## A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → END | Theo CFG của prompt.md. |

## B. Bộ test case

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |

## C. Nhánh không test

Không ghi nhận nhánh không thể test từ CFG cung cấp.
C2 dự kiến = 2 / 2.

## D. File test

```cpp
// FILE: u0600_test.cc
#include "gtest/gtest.h"
#include "ceres/problem_impl.h"
#include "ceres/problem_impl.cc"
#include <map>

namespace ceres {
namespace internal {
// Path P1: START -> 1 -> 2 -> 1 -> END.
TEST(Unit_u0600, PathP1) {
  std::map<CostFunction*, int> items;
  items.emplace(nullptr, 1);
  STLDeleteContainerPairFirstPointers(items.begin(), items.end());
}
}  // namespace internal
}  // namespace ceres
```
