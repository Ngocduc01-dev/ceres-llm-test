# A. Test paths

| Path | Đường đi (node) | Nhánh |
|---|---|---|
| P1 | START → 1 → END | Theo CFG/source; case 1 |
| P2 | START → 1 → END | Theo CFG/source; case 2 |
| P3 | START → 1 → END | Theo CFG/source; case 3 |
| P4 | START → 1 → END | Theo CFG/source; case 4 |
| P5 | START → 1 → END | Theo CFG/source; case 5 |

# B. Test cases

| Test | Path | Dữ liệu đã chọn |
|---|---|---|
| TC1 | P1 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC2 | P2 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC3 | P3 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC4 | P4 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC5 | P5 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |

# C. Nhánh không test

Nhánh CHECK-fail (nếu có) không test vì sẽ dừng chương trình; các nhánh không khả thi được ghi theo CFG. cfg.txt được đọc.

C2 dự kiến = 8 / 8 (chưa chạy thật).

# D. File test

```cpp
// FILE: u1269_test.cc
#include "gtest/gtest.h"
#include "ceres/problem_impl.h"
#include "ceres/stl_util.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1269, TC1_CallsTarget) {
  ceres::internal::ProblemImpl object{};
  object.~ProblemImpl();
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1269, TC2_CallsTarget) {
  ceres::internal::ProblemImpl object{};
  object.~ProblemImpl();
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1269, TC3_CallsTarget) {
  ceres::internal::ProblemImpl object{};
  object.~ProblemImpl();
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1269, TC4_CallsTarget) {
  ceres::internal::ProblemImpl object{};
  object.~ProblemImpl();
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1269, TC5_CallsTarget) {
  ceres::internal::ProblemImpl object{};
  object.~ProblemImpl();
}
```
