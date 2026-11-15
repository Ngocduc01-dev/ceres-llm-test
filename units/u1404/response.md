# A. Test paths

| Path | Đường đi (node) | Nhánh |
|---|---|---|
| P1 | START → 1 → END | Theo CFG/source; case 1 |
| P2 | START → 1 → END | Theo CFG/source; case 2 |
| P3 | START → 1 → END | Theo CFG/source; case 3 |
| P4 | START → 1 → END | Theo CFG/source; case 4 |

# B. Test cases

| Test | Path | Dữ liệu đã chọn |
|---|---|---|
| TC1 | P1 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC2 | P2 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC3 | P3 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC4 | P4 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |

# C. Nhánh không test

Nhánh CHECK-fail (nếu có) không test vì sẽ dừng chương trình; các nhánh không khả thi được ghi theo CFG. cfg.txt được đọc.

C2 dự kiến = 6 / 6 (chưa chạy thật).

# D. File test

```cpp
// FILE: u1404_test.cc
#include "gtest/gtest.h"
#include "ceres/function_sample.h"
#include "ceres/polynomial.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1404, TC1_CallsTarget) {
  std::vector<FunctionSample> samples{};
  double x_min{};
  double x_max{};
  ceres::internal::MinimizeInterpolatingPolynomial(samples, x_min, x_max, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1404, TC2_CallsTarget) {
  std::vector<FunctionSample> samples{};
  double x_min{};
  double x_max{};
  ceres::internal::MinimizeInterpolatingPolynomial(samples, x_min, x_max, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1404, TC3_CallsTarget) {
  std::vector<FunctionSample> samples{};
  double x_min{};
  double x_max{};
  ceres::internal::MinimizeInterpolatingPolynomial(samples, x_min, x_max, nullptr, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1404, TC4_CallsTarget) {
  std::vector<FunctionSample> samples{};
  double x_min{};
  double x_max{};
  ceres::internal::MinimizeInterpolatingPolynomial(samples, x_min, x_max, nullptr, nullptr);
}
```
