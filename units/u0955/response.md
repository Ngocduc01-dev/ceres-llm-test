# A. Test paths

| Path | ???ng ?i (theo s? node) | C?c nh?nh ?i qua |
|---|---|---|
| P1 | START ? 1 ? END | C?c nh?nh kh? thi c?a CFG; bi?n th? d? li?u 1 |

# B. B? test case

| Test | Path | Kho?ng gi? tr? ??u v?o | Gi? tr? ?? ch?n |
|---|---|---|---|
| TC1 | P1 | Tham s? nh?, h?p l? theo ch? k? | Gi? tr? m?c ??nh an to?n |

# C. Nh?nh kh?ng test

Kh?ng c? t?nh ?i v?o c?c nh?nh CHECK l?m ch??ng tr?nh d?ng; c?c nh?nh kh?ng kh? thi ???c ghi nh?n theo CFG.

C2 d? ki?n = 1 / 1

# D. File test

```cpp
// FILE: u0955_test.cc
#include "gtest/gtest.h"
#include "ceres/cgnr_solver.h"
#include "ceres/dense_normal_cholesky_solver.h"
#include "ceres/dense_qr_solver.h"
#include "ceres/dynamic_sparse_normal_cholesky_solver.h"
#include "ceres/iterative_schur_complement_solver.h"
#include "ceres/linear_solver.h"
#include "ceres/schur_complement_solver.h"
#include "ceres/sparse_normal_cholesky_solver.h"

// P1: START -> 1 -> END
TEST(CreateTest, TC1_CallsTarget) {
  LinearSolver object{};
  LinearSolver::Options & options a0{};
  object.Create(a0);
}
```
