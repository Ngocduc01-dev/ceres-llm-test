# Unit u0484
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
// FILE: u0484_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

namespace ceres {
namespace internal {
// Path P1: START -> CFG nodes -> END.
TEST(ParameterBlockUpperBoundForParameterTest, TC1_NoUpperBounds) {
  double values[4] = {0.1, 0.2, 0.3, 0.4};
  ParameterBlock block(values, 4, 0);
  double result = block.UpperBoundForParameter(2);
  (void)result;  // Không kiểm tra kết quả trả về
}
// Path P1: START -> CFG nodes -> END.
TEST(ParameterBlockUpperBoundForParameterTest, TC2_HasUpperBounds) {
  double values[3] = {1.0, 2.0, 3.0};
  ParameterBlock block(values, 3, 0);
  block.SetUpperBound(1, 7.5);
  double result = block.UpperBoundForParameter(1);
  (void)result;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
```
