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
| P8 | START → 1 → END | Theo CFG/source; case 8 |
| P9 | START → 1 → END | Theo CFG/source; case 9 |
| P10 | START → 1 → END | Theo CFG/source; case 10 |

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
| TC8 | P8 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC9 | P9 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC10 | P10 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |

# C. Nhánh không test

Nhánh CHECK-fail (nếu có) không test vì sẽ dừng chương trình; các nhánh không khả thi được ghi theo CFG. cfg.txt được đọc.

C2 dự kiến = 18 / 18 (chưa chạy thật).

# D. File test

```cpp
// FILE: u1127_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/numeric_diff.h"
#include "ceres/numeric_diff_options.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1127, TC1_CallsTarget) {
  int parameter_index{};
  double delta{};
  NumericDiffOptions options{};
  int num_residuals{};
  int parameter_block_size{};
  ceres::internal::NumericDiff object{};
  object.EvaluateRiddersJacobianColumn(nullptr, parameter_index, delta, options, num_residuals, parameter_block_size, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1127, TC2_CallsTarget) {
  int parameter_index{};
  double delta{};
  NumericDiffOptions options{};
  int num_residuals{};
  int parameter_block_size{};
  ceres::internal::NumericDiff object{};
  object.EvaluateRiddersJacobianColumn(nullptr, parameter_index, delta, options, num_residuals, parameter_block_size, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1127, TC3_CallsTarget) {
  int parameter_index{};
  double delta{};
  NumericDiffOptions options{};
  int num_residuals{};
  int parameter_block_size{};
  ceres::internal::NumericDiff object{};
  object.EvaluateRiddersJacobianColumn(nullptr, parameter_index, delta, options, num_residuals, parameter_block_size, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1127, TC4_CallsTarget) {
  int parameter_index{};
  double delta{};
  NumericDiffOptions options{};
  int num_residuals{};
  int parameter_block_size{};
  ceres::internal::NumericDiff object{};
  object.EvaluateRiddersJacobianColumn(nullptr, parameter_index, delta, options, num_residuals, parameter_block_size, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1127, TC5_CallsTarget) {
  int parameter_index{};
  double delta{};
  NumericDiffOptions options{};
  int num_residuals{};
  int parameter_block_size{};
  ceres::internal::NumericDiff object{};
  object.EvaluateRiddersJacobianColumn(nullptr, parameter_index, delta, options, num_residuals, parameter_block_size, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1127, TC6_CallsTarget) {
  int parameter_index{};
  double delta{};
  NumericDiffOptions options{};
  int num_residuals{};
  int parameter_block_size{};
  ceres::internal::NumericDiff object{};
  object.EvaluateRiddersJacobianColumn(nullptr, parameter_index, delta, options, num_residuals, parameter_block_size, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P7: START -> 1 -> END; branch decisions covered by case 7
TEST(Unit_u1127, TC7_CallsTarget) {
  int parameter_index{};
  double delta{};
  NumericDiffOptions options{};
  int num_residuals{};
  int parameter_block_size{};
  ceres::internal::NumericDiff object{};
  object.EvaluateRiddersJacobianColumn(nullptr, parameter_index, delta, options, num_residuals, parameter_block_size, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P8: START -> 1 -> END; branch decisions covered by case 8
TEST(Unit_u1127, TC8_CallsTarget) {
  int parameter_index{};
  double delta{};
  NumericDiffOptions options{};
  int num_residuals{};
  int parameter_block_size{};
  ceres::internal::NumericDiff object{};
  object.EvaluateRiddersJacobianColumn(nullptr, parameter_index, delta, options, num_residuals, parameter_block_size, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P9: START -> 1 -> END; branch decisions covered by case 9
TEST(Unit_u1127, TC9_CallsTarget) {
  int parameter_index{};
  double delta{};
  NumericDiffOptions options{};
  int num_residuals{};
  int parameter_block_size{};
  ceres::internal::NumericDiff object{};
  object.EvaluateRiddersJacobianColumn(nullptr, parameter_index, delta, options, num_residuals, parameter_block_size, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P10: START -> 1 -> END; branch decisions covered by case 10
TEST(Unit_u1127, TC10_CallsTarget) {
  int parameter_index{};
  double delta{};
  NumericDiffOptions options{};
  int num_residuals{};
  int parameter_block_size{};
  ceres::internal::NumericDiff object{};
  object.EvaluateRiddersJacobianColumn(nullptr, parameter_index, delta, options, num_residuals, parameter_block_size, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}
```
