# Unit u0537
## A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → END | Theo CFG của prompt.md. |
| P2 | START → 1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → END | Theo CFG của prompt.md. |
| P3 | START → 1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → END | Theo CFG của prompt.md. |
| P4 | START → 1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → END | Theo CFG của prompt.md. |
| P5 | START → 1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → END | Theo CFG của prompt.md. |
| P6 | START → 1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → END | Theo CFG của prompt.md. |
| P7 | START → 1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → END | Theo CFG của prompt.md. |
| P8 | START → 1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → END | Theo CFG của prompt.md. |
| P9 | START → 1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → END | Theo CFG của prompt.md. |
| P10 | START → 1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → END | Theo CFG của prompt.md. |

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
| TC10 | P10 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |

## C. Nhánh không test

Không ghi nhận nhánh không thể test từ CFG cung cấp.
C2 dự kiến = 6 / 6.

## D. File test

```cpp
// FILE: u0537_test.cc
#include "gtest/gtest.h"
#include "ceres/array_utils.h"

namespace ceres {
namespace internal {

// P1: node 1: đúng -> node 2 -> END
// Path P1: START -> CFG nodes -> END.
TEST(FindInvalidValueTest, TC1_NullPointer) {
  FindInvalidValue(3, nullptr);
}

// P2: node 1: sai, node 4: sai (0 lần lặp)
// Path P1: START -> CFG nodes -> END.
TEST(FindInvalidValueTest, TC2_ZeroIterations) {
  const double x[] = {7.0};
  FindInvalidValue(0, x);
}

// P3 (k=1): node 1: sai, node 4: đúng 1 lần rồi sai, node 5: sai
// Path P1: START -> CFG nodes -> END.
TEST(FindInvalidValueTest, TC3_OneIteration) {
  const double x[] = {2.5};
  FindInvalidValue(1, x);
}

// P3 (k=2): node 1: sai, node 4: đúng 2 lần rồi sai, node 5: sai
// Path P1: START -> CFG nodes -> END.
TEST(FindInvalidValueTest, TC4_TwoIterations) {
  const double x[] = {-3.0, 4.5};
  FindInvalidValue(2, x);
}

// P3 (k=3): node 1: sai, node 4: đúng 3 lần rồi sai, node 5: sai
// Path P1: START -> CFG nodes -> END.
TEST(FindInvalidValueTest, TC5_MiddleIterations) {
  const double x[] = {1.5, -6.0, 8.0};
  FindInvalidValue(3, x);
}

// P3 (k=4): node 1: sai, node 4: đúng 4 lần rồi sai, node 5: sai
// Path P1: START -> CFG nodes -> END.
TEST(FindInvalidValueTest, TC6_NMinusOneIterations) {
  const double x[] = {0.5, -1.0, 9.0, -7.5};
  FindInvalidValue(4, x);
}

// P3 (k=5): node 1: sai, node 4: đúng 5 lần rồi sai, node 5: sai
// Path P1: START -> CFG nodes -> END.
TEST(FindInvalidValueTest, TC7_NIterations) {
  const double x[] = {3.0, -2.0, 6.5, -4.0, 1.0};
  FindInvalidValue(5, x);
}

// P4: node 1: sai, node 4: đúng, node 5: đúng (NaN ở phần tử đầu)
// Path P1: START -> CFG nodes -> END.
TEST(FindInvalidValueTest, TC8_NaNAtFirstElement) {
  const double x[] = {std::numeric_limits<double>::quiet_NaN(), 1.0, 2.0};
  FindInvalidValue(3, x);
}

// P5: node 1: sai, node 4: đúng, node 5: sai, sai, đúng (vô cực ở index 2)
// Path P1: START -> CFG nodes -> END.
TEST(FindInvalidValueTest, TC9_InfinityAtThirdElement) {
  const double x[] = {1.0, -2.0, std::numeric_limits<double>::infinity(), 5.0};
  FindInvalidValue(4, x);
}

// P6: node 1: sai, node 4: đúng, node 5: đúng ở lần 5 (x[i] == 1e302, tức kImpossibleValue)
// Path P1: START -> CFG nodes -> END.
TEST(FindInvalidValueTest, TC10_ImpossibleValueAtLastElement) {
  const double x[] = {1.0, 2.0, -3.0, 4.0, 1e302};
  FindInvalidValue(5, x);
}

}  // namespace internal
}  // namespace ceres
```
