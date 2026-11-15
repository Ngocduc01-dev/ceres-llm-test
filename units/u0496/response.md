# Unit u0496
## A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → 4 → END | Theo CFG của prompt.md. |
| P2 | START → 1 → 2 → 3 → 4 → END | Theo CFG của prompt.md. |
| P3 | START → 1 → 2 → 3 → 4 → END | Theo CFG của prompt.md. |
| P4 | START → 1 → 2 → 3 → 4 → END | Theo CFG của prompt.md. |

## B. Bộ test case

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |
| TC2 | P2 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |
| TC3 | P3 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |
| TC4 | P4 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |

## C. Nhánh không test

Không ghi nhận nhánh không thể test từ CFG cung cấp.
C2 dự kiến = 4 / 4.

## D. File test

```cpp
// FILE: u0496_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/numeric_diff.h"
#include "ceres/numeric_diff_options.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0496, PathP1) {
  const NumericDiffOptions& arg_2{}
  const CostFunctor* arg_0 = nullptr;
  const double* arg_1 = nullptr;
  const NumericDiffOptions& arg_2{};
  int arg_3 = 1;
  double** arg_4 = nullptr;
  double** arg_5 = nullptr;
  ceres::EvaluateJacobianForParameterBlocks<ParameterDims<false, 4>>::Apply<CENTRAL, 1, QuadraticCostFunctor> target(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5);
  target.Apply(nullptr, nullptr, arg_2, 1, nullptr, nullptr);
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0496, PathP2) {
  const NumericDiffOptions& arg_2{}
  const CostFunctor* arg_0 = nullptr;
  const double* arg_1 = nullptr;
  const NumericDiffOptions& arg_2{};
  int arg_3 = 1;
  double** arg_4 = nullptr;
  double** arg_5 = nullptr;
  ceres::EvaluateJacobianForParameterBlocks<ParameterDims<false, 4>>::Apply<CENTRAL, 1, QuadraticCostFunctor> target(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5);
  target.Apply(nullptr, nullptr, arg_2, 1, nullptr, nullptr);
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0496, PathP3) {
  const NumericDiffOptions& arg_2{}
  const CostFunctor* arg_0 = nullptr;
  const double* arg_1 = nullptr;
  const NumericDiffOptions& arg_2{};
  int arg_3 = 1;
  double** arg_4 = nullptr;
  double** arg_5 = nullptr;
  ceres::EvaluateJacobianForParameterBlocks<ParameterDims<false, 4>>::Apply<CENTRAL, 1, QuadraticCostFunctor> target(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5);
  target.Apply(nullptr, nullptr, arg_2, 1, nullptr, nullptr);
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0496, PathP4) {
  const NumericDiffOptions& arg_2{}
  const CostFunctor* arg_0 = nullptr;
  const double* arg_1 = nullptr;
  const NumericDiffOptions& arg_2{};
  int arg_3 = 1;
  double** arg_4 = nullptr;
  double** arg_5 = nullptr;
  ceres::EvaluateJacobianForParameterBlocks<ParameterDims<false, 4>>::Apply<CENTRAL, 1, QuadraticCostFunctor> target(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5);
  target.Apply(nullptr, nullptr, arg_2, 1, nullptr, nullptr);
}
```
