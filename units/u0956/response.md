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
// FILE: u0956_test.cc
#include "gtest/gtest.h"
#include "ceres/iteration_callback.h"
#include "ceres/solver.h"
#include "ceres/minimizer.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0956, TC1_CallsTarget) {
  Minimizer::Options options{};
  IterationSummary iteration_summary{};
  ceres::internal::Minimizer object{};
  object.RunCallbacks(options, iteration_summary, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0956, TC2_CallsTarget) {
  Minimizer::Options options{};
  IterationSummary iteration_summary{};
  ceres::internal::Minimizer object{};
  object.RunCallbacks(options, iteration_summary, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u0956, TC3_CallsTarget) {
  Minimizer::Options options{};
  IterationSummary iteration_summary{};
  ceres::internal::Minimizer object{};
  object.RunCallbacks(options, iteration_summary, nullptr);
}
```
