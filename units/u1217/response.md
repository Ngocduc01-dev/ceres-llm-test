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

C2 d? ki?n = 22 / 22

# D. File test

```cpp
// FILE: u1217_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/covariance_impl.h"
#include "ceres/map_util.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"

// P1: START -> 1 -> END
TEST(GetCovarianceBlockInTangentOrAmbientSpaceTest, TC1_CallsTarget) {
  CovarianceImpl object{};
  double a0[5] = {};
  double a1[5] = {};
  bool a2 = false;
  double a3[5] = {};
  object.GetCovarianceBlockInTangentOrAmbientSpace(a0, a1, a2, a3);
}

// P2: START -> 1 -> END
TEST(GetCovarianceBlockInTangentOrAmbientSpaceTest, TC2_CallsTarget) {
  CovarianceImpl object{};
  double a0[5] = {};
  double a1[5] = {};
  bool a2 = false;
  double a3[5] = {};
  object.GetCovarianceBlockInTangentOrAmbientSpace(a0, a1, a2, a3);
}

// P3: START -> 1 -> END
TEST(GetCovarianceBlockInTangentOrAmbientSpaceTest, TC3_CallsTarget) {
  CovarianceImpl object{};
  double a0[5] = {};
  double a1[5] = {};
  bool a2 = false;
  double a3[5] = {};
  object.GetCovarianceBlockInTangentOrAmbientSpace(a0, a1, a2, a3);
}
```
