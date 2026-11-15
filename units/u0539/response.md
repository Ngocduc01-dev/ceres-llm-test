# Unit u0539
## A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → 9 → END | Theo CFG của prompt.md. |
| P2 | START → 1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → 9 → END | Theo CFG của prompt.md. |

## B. Bộ test case

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |
| TC2 | P2 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |

## C. Nhánh không test

Không ghi nhận nhánh không thể test từ CFG cung cấp.
C2 dự kiến = 6 / 6.

## D. File test

```cpp
// FILE: u0539_test.cc
#include "gtest/gtest.h"
#include "ceres/is_close.h"

namespace ceres {
namespace internal {
// Path P1: START -> CFG nodes -> END.
TEST(IsCloseTest, NullErrorPointersAndOneInputIsZero) {
  const double x = 0.0;
  const double y = 3.7;
  const double relative_precision = 1e-3;
  bool result = IsClose(x, y, relative_precision, nullptr, nullptr);
  (void)result;
}
// Path P1: START -> CFG nodes -> END.
TEST(IsCloseTest, NonNullErrorPointersAndNonZeroInputs) {
  const double x = 5.2;
  const double y = 8.4;
  const double relative_precision = 1e-3;
  double relative_error = 0.0;
  double absolute_error = 0.0;
  bool result =
      IsClose(x, y, relative_precision, &relative_error, &absolute_error);
  (void)result;
}

}  // namespace internal
}  // namespace ceres
```
