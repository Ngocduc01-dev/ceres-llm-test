# Unit u0400
## A. Test paths

| Path | ???ng ?i (theo s? node) | C?c nh?nh ?i qua |
|---|---|---|
| P1 | START ? 1 ? END | Kh?ng c? ?i?m r? nh?nh trong CFG. |

## B. B? test case

| Test | Path | Kho?ng gi? tr? ??u v?o | Gi? tr? ?? ch?n |
|---|---|---|---|
| TC1 | P1 | Theo ch? k? `void Init(int max_parameters_per_residual_block, int max_scratch_doubles_needed_for_evaluate, int max_residuals_per_residual_block, int num_parameters)` | Gi? tr? h?p l? trong file test |

## C. Nh?nh kh?ng test

Kh?ng c? nh?nh ?i?u khi?n. C2 d? ki?n = 0 / 0.

## D. File test

```cpp
// FILE: u0400_test.cc
#include "gtest/gtest.h"
#include "ceres/program_evaluator.h"
// Path P1: START -> 1 -> END.
TEST(Unit_u0400, PathP1) { ceres::internal::ProgramEvaluator::EvaluateScratch target; target.Init(1, 1, 1, 1); }
```
