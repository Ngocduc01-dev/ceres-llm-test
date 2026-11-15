# Unit u0482
## A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → END | Theo CFG của prompt.md. |
| P2 | START → 1 → 2 → END | Theo CFG của prompt.md. |

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
// FILE: u0482_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"
#include "ceres/parameter_block.h"

namespace ceres {
namespace internal {

// P1: START -> 1 (đúng: manifold_ == nullptr) -> 2 -> END
// Path P1: START -> CFG nodes -> END.
TEST(ParameterBlockTangentSizeTest, TC1_NoManifold) {
  double values[3] = {1.0, 2.0, 3.0};
  ParameterBlock block(values, 3, 0);
  block.TangentSize();
}

// P2: START -> 1 (sai: manifold_ != nullptr) -> 2 -> END
// Path P1: START -> CFG nodes -> END.
TEST(ParameterBlockTangentSizeTest, TC2_WithManifold) {
  double values[3] = {1.0, 2.0, 3.0};
  EuclideanManifold<3> manifold;
  ParameterBlock block(values, 3, 0, &manifold);
  block.TangentSize();
}

}  // namespace internal
}  // namespace ceres
```
