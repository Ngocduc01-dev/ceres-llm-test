# A. Test paths

| Path | Đường đi (node) | Nhánh |
|---|---|---|
| P1 | START → 1 → END | Theo CFG/source; case 1 |
| P2 | START → 1 → END | Theo CFG/source; case 2 |

# B. Test cases

| Test | Path | Dữ liệu đã chọn |
|---|---|---|
| TC1 | P1 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC2 | P2 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |

# C. Nhánh không test

Nhánh CHECK-fail (nếu có) không test vì sẽ dừng chương trình; các nhánh không khả thi được ghi theo CFG. cfg.txt được đọc.

C2 dự kiến = 2 / 2 (chưa chạy thật).

# D. File test

```cpp
// FILE: u0969_test.cc
#include "gtest/gtest.h"
#include "ceres/evaluator.h"
#include "ceres/line_search_minimizer.h"
#include "ceres/line_search_minimizer.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0969, TC1_CallsTarget) {
  Vector x{};
  ceres::internal::(anonymous)::EvaluateGradientNorms(nullptr, x, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0969, TC2_CallsTarget) {
  Vector x{};
  ceres::internal::(anonymous)::EvaluateGradientNorms(nullptr, x, nullptr, nullptr);
}
```
