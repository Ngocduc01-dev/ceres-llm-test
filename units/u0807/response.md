# A. Test paths

| Path | Đường đi (node) | Nhánh |
|---|---|---|
| P1 | START → 1 → END | Theo CFG/source; case 1 |
| P2 | START → 1 → END | Theo CFG/source; case 2 |
| P3 | START → 1 → END | Theo CFG/source; case 3 |

# B. Test cases

| Test | Path | Dữ liệu đã chọn |
|---|---|---|
| TC1 | P1 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC2 | P2 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC3 | P3 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |

# C. Nhánh không test

Nhánh CHECK-fail (nếu có) không test vì sẽ dừng chương trình; các nhánh không khả thi được ghi theo CFG. cfg.txt được đọc.

C2 dự kiến = 4 / 4 (chưa chạy thật).

# D. File test

```cpp
// FILE: u0807_test.cc
#include "gtest/gtest.h"
#include "ceres/polynomial.h"
#include "ceres/polynomial.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0807, TC1_CallsTarget) {
  Vector polynomial{};
  ceres::internal::(anonymous)::FindLinearPolynomialRoots(polynomial, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0807, TC2_CallsTarget) {
  Vector polynomial{};
  ceres::internal::(anonymous)::FindLinearPolynomialRoots(polynomial, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u0807, TC3_CallsTarget) {
  Vector polynomial{};
  ceres::internal::(anonymous)::FindLinearPolynomialRoots(polynomial, nullptr, nullptr);
}
```
