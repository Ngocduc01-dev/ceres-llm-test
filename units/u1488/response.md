# A. Test paths

| Path | Đường đi (node) | Nhánh |
|---|---|---|
| P1 | START → 1 → END | Theo CFG/source; case 1 |
| P2 | START → 1 → END | Theo CFG/source; case 2 |
| P3 | START → 1 → END | Theo CFG/source; case 3 |
| P4 | START → 1 → END | Theo CFG/source; case 4 |
| P5 | START → 1 → END | Theo CFG/source; case 5 |
| P6 | START → 1 → END | Theo CFG/source; case 6 |

# B. Test cases

| Test | Path | Dữ liệu đã chọn |
|---|---|---|
| TC1 | P1 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC2 | P2 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC3 | P3 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC4 | P4 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC5 | P5 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC6 | P6 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |

# C. Nhánh không test

Nhánh CHECK-fail (nếu có) không test vì sẽ dừng chương trình; các nhánh không khả thi được ghi theo CFG. cfg.txt được đọc.

C2 dự kiến = 10 / 10 (chưa chạy thật).

# D. File test

```cpp
// FILE: u1488_test.cc
#include "gtest/gtest.h"
#include "ceres/function_sample.h"
#include "ceres/line_search.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1488, TC1_CallsTarget) {
  LineSearchInterpolationType interpolation_type{};
  FunctionSample lowerbound{};
  FunctionSample previous{};
  FunctionSample current{};
  const double min_step_size{};
  const double max_step_size{};
  ceres::internal::LineSearch object{};
  object.InterpolatingPolynomialMinimizingStepSize(interpolation_type, lowerbound, previous, current, min_step_size, max_step_size);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1488, TC2_CallsTarget) {
  LineSearchInterpolationType interpolation_type{};
  FunctionSample lowerbound{};
  FunctionSample previous{};
  FunctionSample current{};
  const double min_step_size{};
  const double max_step_size{};
  ceres::internal::LineSearch object{};
  object.InterpolatingPolynomialMinimizingStepSize(interpolation_type, lowerbound, previous, current, min_step_size, max_step_size);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1488, TC3_CallsTarget) {
  LineSearchInterpolationType interpolation_type{};
  FunctionSample lowerbound{};
  FunctionSample previous{};
  FunctionSample current{};
  const double min_step_size{};
  const double max_step_size{};
  ceres::internal::LineSearch object{};
  object.InterpolatingPolynomialMinimizingStepSize(interpolation_type, lowerbound, previous, current, min_step_size, max_step_size);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1488, TC4_CallsTarget) {
  LineSearchInterpolationType interpolation_type{};
  FunctionSample lowerbound{};
  FunctionSample previous{};
  FunctionSample current{};
  const double min_step_size{};
  const double max_step_size{};
  ceres::internal::LineSearch object{};
  object.InterpolatingPolynomialMinimizingStepSize(interpolation_type, lowerbound, previous, current, min_step_size, max_step_size);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1488, TC5_CallsTarget) {
  LineSearchInterpolationType interpolation_type{};
  FunctionSample lowerbound{};
  FunctionSample previous{};
  FunctionSample current{};
  const double min_step_size{};
  const double max_step_size{};
  ceres::internal::LineSearch object{};
  object.InterpolatingPolynomialMinimizingStepSize(interpolation_type, lowerbound, previous, current, min_step_size, max_step_size);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1488, TC6_CallsTarget) {
  LineSearchInterpolationType interpolation_type{};
  FunctionSample lowerbound{};
  FunctionSample previous{};
  FunctionSample current{};
  const double min_step_size{};
  const double max_step_size{};
  ceres::internal::LineSearch object{};
  object.InterpolatingPolynomialMinimizingStepSize(interpolation_type, lowerbound, previous, current, min_step_size, max_step_size);
}
```
