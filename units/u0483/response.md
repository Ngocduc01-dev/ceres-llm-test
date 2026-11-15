# Unit u0483
## A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → END | Theo CFG của prompt.md. |
| P2 | START → 1 → 2 → 3 → END | Theo CFG của prompt.md. |

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
// FILE: u0483_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

namespace ceres {
namespace internal {

// TC1 - P1: node 1: đúng (lower_bounds_ == nullptr) -> node 2 -> END
// Path P1: START -> CFG nodes -> END.
TEST(ParameterBlockLowerBoundForParameter, NoLowerBoundsSet) {
  double x[3] = {0.5, 1.5, 2.5};
  ParameterBlock block(x, 3, 0);
  volatile double result = block.LowerBoundForParameter(1);
  (void)result;
}

// TC2 - P2: node 1: sai (lower_bounds_ != nullptr) -> node 3 -> END
// Path P1: START -> CFG nodes -> END.
TEST(ParameterBlockLowerBoundForParameter, LowerBoundsSet) {
  double x[3] = {0.5, 1.5, 2.5};
  ParameterBlock block(x, 3, 0);
  block.SetLowerBound(1, -2.5);
  volatile double result = block.LowerBoundForParameter(1);
  (void)result;
}

}  // namespace internal
}  // namespace ceres
```
