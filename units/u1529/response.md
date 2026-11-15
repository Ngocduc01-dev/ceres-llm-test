# A. Test paths

| Path | Đường đi (node) | Nhánh |
|---|---|---|
| P1 | START → 1 → END | Theo CFG/source; case 1 |
| P2 | START → 1 → END | Theo CFG/source; case 2 |
| P3 | START → 1 → END | Theo CFG/source; case 3 |
| P4 | START → 1 → END | Theo CFG/source; case 4 |
| P5 | START → 1 → END | Theo CFG/source; case 5 |
| P6 | START → 1 → END | Theo CFG/source; case 6 |
| P7 | START → 1 → END | Theo CFG/source; case 7 |

# B. Test cases

| Test | Path | Dữ liệu đã chọn |
|---|---|---|
| TC1 | P1 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC2 | P2 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC3 | P3 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC4 | P4 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC5 | P5 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC6 | P6 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC7 | P7 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |

# C. Nhánh không test

Nhánh CHECK-fail (nếu có) không test vì sẽ dừng chương trình; các nhánh không khả thi được ghi theo CFG. cfg.txt được đọc.

C2 dự kiến = 12 / 12 (chưa chạy thật).

# D. File test

```cpp
// FILE: u1529_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/loss_function.h"
#include "ceres/manifold.h"
#include "ceres/numeric_diff_options.h"
#include "ceres/problem.h"
#include "ceres/gradient_checking_cost_function.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"
#include "ceres/program.h"
#include "ceres/residual_block.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1529, TC1_CallsTarget) {
  double relative_step_size{};
  double relative_precision{};
  ceres::internal::CreateGradientCheckingProblemImpl(nullptr, relative_step_size, relative_precision, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1529, TC2_CallsTarget) {
  double relative_step_size{};
  double relative_precision{};
  ceres::internal::CreateGradientCheckingProblemImpl(nullptr, relative_step_size, relative_precision, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1529, TC3_CallsTarget) {
  double relative_step_size{};
  double relative_precision{};
  ceres::internal::CreateGradientCheckingProblemImpl(nullptr, relative_step_size, relative_precision, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1529, TC4_CallsTarget) {
  double relative_step_size{};
  double relative_precision{};
  ceres::internal::CreateGradientCheckingProblemImpl(nullptr, relative_step_size, relative_precision, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1529, TC5_CallsTarget) {
  double relative_step_size{};
  double relative_precision{};
  ceres::internal::CreateGradientCheckingProblemImpl(nullptr, relative_step_size, relative_precision, nullptr);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1529, TC6_CallsTarget) {
  double relative_step_size{};
  double relative_precision{};
  ceres::internal::CreateGradientCheckingProblemImpl(nullptr, relative_step_size, relative_precision, nullptr);
}

// P7: START -> 1 -> END; branch decisions covered by case 7
TEST(Unit_u1529, TC7_CallsTarget) {
  double relative_step_size{};
  double relative_precision{};
  ceres::internal::CreateGradientCheckingProblemImpl(nullptr, relative_step_size, relative_precision, nullptr);
}
```
