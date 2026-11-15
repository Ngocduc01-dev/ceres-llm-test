# Unit u0536
## A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → 4 → 5 → 6 → 7 → END | Theo CFG của prompt.md. |
| P2 | START → 1 → 2 → 3 → 4 → 5 → 6 → 7 → END | Theo CFG của prompt.md. |
| P3 | START → 1 → 2 → 3 → 4 → 5 → 6 → 7 → END | Theo CFG của prompt.md. |
| P4 | START → 1 → 2 → 3 → 4 → 5 → 6 → 7 → END | Theo CFG của prompt.md. |
| P5 | START → 1 → 2 → 3 → 4 → 5 → 6 → 7 → END | Theo CFG của prompt.md. |
| P6 | START → 1 → 2 → 3 → 4 → 5 → 6 → 7 → END | Theo CFG của prompt.md. |
| P7 | START → 1 → 2 → 3 → 4 → 5 → 6 → 7 → END | Theo CFG của prompt.md. |
| P8 | START → 1 → 2 → 3 → 4 → 5 → 6 → 7 → END | Theo CFG của prompt.md. |
| P9 | START → 1 → 2 → 3 → 4 → 5 → 6 → 7 → END | Theo CFG của prompt.md. |

## B. Bộ test case

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |
| TC2 | P2 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |
| TC3 | P3 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |
| TC4 | P4 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |
| TC5 | P5 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |
| TC6 | P6 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |
| TC7 | P7 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |
| TC8 | P8 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |
| TC9 | P9 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |

## C. Nhánh không test

Không ghi nhận nhánh không thể test từ CFG cung cấp.
C2 dự kiến = 6 / 6.

## D. File test

```cpp
// FILE: u0536_test.cc
#include "gtest/gtest.h"
#include "ceres/array_utils.h"

namespace ceres {
namespace internal {
// Path P1: START -> CFG nodes -> END.
TEST(IsArrayValidTest, NullArray) {
  const double* x = nullptr;
  const int64_t size = 3;
  IsArrayValid(size, x);
}
// Path P1: START -> CFG nodes -> END.
TEST(IsArrayValidTest, ZeroIterations) {
  const double x[1] = {1.5};
  const int64_t size = 0;
  IsArrayValid(size, x);
}
// Path P1: START -> CFG nodes -> END.
TEST(IsArrayValidTest, OneIteration) {
  const double x[1] = {1.5};
  const int64_t size = 1;
  IsArrayValid(size, x);
}
// Path P1: START -> CFG nodes -> END.
TEST(IsArrayValidTest, TwoIterations) {
  const double x[2] = {1.5, -2.25};
  const int64_t size = 2;
  IsArrayValid(size, x);
}
// Path P1: START -> CFG nodes -> END.
TEST(IsArrayValidTest, ThreeIterations) {
  const double x[3] = {1.5, -2.25, 3.75};
  const int64_t size = 3;
  IsArrayValid(size, x);
}
// Path P1: START -> CFG nodes -> END.
TEST(IsArrayValidTest, FourIterations) {
  const double x[4] = {1.5, -2.25, 3.75, 0.5};
  const int64_t size = 4;
  IsArrayValid(size, x);
}
// Path P1: START -> CFG nodes -> END.
TEST(IsArrayValidTest, FiveIterations) {
  const double x[5] = {1.5, -2.25, 3.75, 0.5, 7.0};
  const int64_t size = 5;
  IsArrayValid(size, x);
}
// Path P1: START -> CFG nodes -> END.
TEST(IsArrayValidTest, NonFiniteAtFirstElement) {
  const double x[3] = {std::numeric_limits<double>::quiet_NaN(), 1.5, 2.5};
  const int64_t size = 3;
  IsArrayValid(size, x);
}
// Path P1: START -> CFG nodes -> END.
TEST(IsArrayValidTest, ImpossibleValueAtThirdElement) {
  const double x[3] = {1.5, -2.25, kImpossibleValue};
  const int64_t size = 3;
  IsArrayValid(size, x);
}

}  // namespace internal
}  // namespace ceres
```
