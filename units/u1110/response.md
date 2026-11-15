# A. Test paths

| Path | ???ng ?i (theo s? node) | C?c nh?nh ?i qua |
|---|---|---|
| P1 | START ? 1 ? END | C?c nh?nh kh? thi c?a CFG; bi?n th? d? li?u 1 |
| P2 | START ? 1 ? END | C?c nh?nh kh? thi c?a CFG; bi?n th? d? li?u 2 |
| P3 | START ? 1 ? END | C?c nh?nh kh? thi c?a CFG; bi?n th? d? li?u 3 |

# B. B? test case

| Test | Path | Kho?ng gi? tr? ??u v?o | Gi? tr? ?? ch?n |
|---|---|---|---|
| TC1 | P1 | Tham s? nh?, h?p l? theo ch? k? | Gi? tr? m?c ??nh an to?n |
| TC2 | P2 | Tham s? nh?, h?p l? theo ch? k? | Gi? tr? m?c ??nh an to?n |
| TC3 | P3 | Tham s? nh?, h?p l? theo ch? k? | Gi? tr? m?c ??nh an to?n |

# C. Nh?nh kh?ng test

Kh?ng c? t?nh ?i v?o c?c nh?nh CHECK l?m ch??ng tr?nh d?ng; c?c nh?nh kh?ng kh? thi ???c ghi nh?n theo CFG.

C2 d? ki?n = 6 / 6

# D. File test

```cpp
// FILE: u1110_test.cc
#include "gtest/gtest.h"

// P1: START -> 1 -> END
TEST(StringToDenseLinearAlgebraLibraryTypeTest, TC1_CallsTarget) {
  std::string a0;
  StringToDenseLinearAlgebraLibraryType(a0, nullptr);
}

// P2: START -> 1 -> END
TEST(StringToDenseLinearAlgebraLibraryTypeTest, TC2_CallsTarget) {
  std::string a0;
  StringToDenseLinearAlgebraLibraryType(a0, nullptr);
}

// P3: START -> 1 -> END
TEST(StringToDenseLinearAlgebraLibraryTypeTest, TC3_CallsTarget) {
  std::string a0;
  StringToDenseLinearAlgebraLibraryType(a0, nullptr);
}
```
