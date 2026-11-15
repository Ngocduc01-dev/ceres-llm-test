# Unit u0750
## A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → 4 → 5 → 6 → END | Theo CFG của prompt.md. |

## B. Bộ test case

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |

## C. Nhánh không test

Không ghi nhận nhánh không thể test từ CFG cung cấp.
C2 dự kiến = 2 / 2.

## D. File test

```cpp
// FILE: u0750_test.cc
#include "gtest/gtest.h"
#include "ceres/linear_solver.h"
#include <sstream>

// Path P1: START -> 1 -> END.
TEST(Unit_u0750, PathP1) {
  std::ostringstream stream;
  ceres::internal::operator<<(stream, ceres::internal::OrderingType::NATURAL);
}
```
