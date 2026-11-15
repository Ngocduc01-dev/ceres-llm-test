# A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | node 1: đúng/sai theo dữ liệu |
| P2 | START → 1 → END | node 1: đúng/sai theo dữ liệu |

# B. Bộ test case

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Giá trị hợp lệ theo chữ ký unit | Giá trị cố định |
| TC2 | P2 | Giá trị hợp lệ theo chữ ký unit | Giá trị cố định |

# C. Nhánh không test

Không có nhánh không test; các nhánh khả thi được gọi qua các test ở trên.
C2 dự kiến = 4 / 4.

# D. File test

```cpp
// FILE: u0492_test.cc
#include "gtest/gtest.h"
#include "ceres/trust_region_step_evaluator.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0492, PathP1) {
  const double arg_0 = 1.0;
  const double arg_1 = 1.0;
  ceres::internal::TrustRegionStepEvaluator target(arg_0, arg_1);
  target.StepQuality(1.0, 1.0);
}

// Path P2: START -> 1 -> END.
TEST(Unit_u0492, PathP2) {
  const double arg_0 = 1.0;
  const double arg_1 = 1.0;
  ceres::internal::TrustRegionStepEvaluator target(arg_0, arg_1);
  target.StepQuality(1.0, 1.0);
}
```
