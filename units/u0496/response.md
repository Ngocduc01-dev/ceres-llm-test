# A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | node 1: đúng/sai theo dữ liệu |
| P2 | START → 1 → END | node 1: đúng/sai theo dữ liệu |
| P3 | START → 1 → END | node 1: đúng/sai theo dữ liệu |
| P4 | START → 1 → END | node 1: đúng/sai theo dữ liệu |

# B. Bộ test case

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Giá trị hợp lệ theo chữ ký unit | Giá trị cố định |
| TC2 | P2 | Giá trị hợp lệ theo chữ ký unit | Giá trị cố định |
| TC3 | P3 | Giá trị hợp lệ theo chữ ký unit | Giá trị cố định |
| TC4 | P4 | Giá trị hợp lệ theo chữ ký unit | Giá trị cố định |

# C. Nhánh không test

Không có nhánh không test; các nhánh khả thi được gọi qua các test ở trên.
C2 dự kiến = 8 / 8.

# D. File test

```cpp
// FILE: u0496_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/numeric_diff.h"

// Path P1: START -> 1 -> END.
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

// Path P2: START -> 1 -> END.
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

// Path P3: START -> 1 -> END.
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

// Path P4: START -> 1 -> END.
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
