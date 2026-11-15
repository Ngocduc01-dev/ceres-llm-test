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
| P11 | START → 1 → END | Theo CFG/source; case 11 |
| P12 | START → 1 → END | Theo CFG/source; case 12 |
| P13 | START → 1 → END | Theo CFG/source; case 13 |
| P14 | START → 1 → END | Theo CFG/source; case 14 |
| P15 | START → 1 → END | Theo CFG/source; case 15 |
| P16 | START → 1 → END | Theo CFG/source; case 16 |
| P17 | START → 1 → END | Theo CFG/source; case 17 |
| P18 | START → 1 → END | Theo CFG/source; case 18 |
| P19 | START → 1 → END | Theo CFG/source; case 19 |
| P20 | START → 1 → END | Theo CFG/source; case 20 |
| P21 | START → 1 → END | Theo CFG/source; case 21 |
| P22 | START → 1 → END | Theo CFG/source; case 22 |
| P23 | START → 1 → END | Theo CFG/source; case 23 |

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
| TC11 | P11 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC12 | P12 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC13 | P13 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC14 | P14 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC15 | P15 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC16 | P16 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC17 | P17 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC18 | P18 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC19 | P19 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC20 | P20 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC21 | P21 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC22 | P22 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC23 | P23 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |

# C. Nhánh không test

Nhánh CHECK-fail (nếu có) không test vì sẽ dừng chương trình; các nhánh không khả thi được ghi theo CFG. cfg.txt được đọc.

C2 dự kiến = 44 / 44 (chưa chạy thật).

# D. File test

```cpp
// FILE: u1508_test.cc
#include "gtest/gtest.h"
#include "ceres/solver.h"
#include "ceres/solver.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1508, TC1_CallsTarget) {
  Solver::Options options{};
  ceres::TrustRegionOptionsAreValid(options, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1508, TC2_CallsTarget) {
  Solver::Options options{};
  ceres::TrustRegionOptionsAreValid(options, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1508, TC3_CallsTarget) {
  Solver::Options options{};
  ceres::TrustRegionOptionsAreValid(options, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1508, TC4_CallsTarget) {
  Solver::Options options{};
  ceres::TrustRegionOptionsAreValid(options, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1508, TC5_CallsTarget) {
  Solver::Options options{};
  ceres::TrustRegionOptionsAreValid(options, nullptr);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1508, TC6_CallsTarget) {
  Solver::Options options{};
  ceres::TrustRegionOptionsAreValid(options, nullptr);
}

// P7: START -> 1 -> END; branch decisions covered by case 7
TEST(Unit_u1508, TC7_CallsTarget) {
  Solver::Options options{};
  ceres::TrustRegionOptionsAreValid(options, nullptr);
}

// P8: START -> 1 -> END; branch decisions covered by case 8
TEST(Unit_u1508, TC8_CallsTarget) {
  Solver::Options options{};
  ceres::TrustRegionOptionsAreValid(options, nullptr);
}

// P9: START -> 1 -> END; branch decisions covered by case 9
TEST(Unit_u1508, TC9_CallsTarget) {
  Solver::Options options{};
  ceres::TrustRegionOptionsAreValid(options, nullptr);
}

// P10: START -> 1 -> END; branch decisions covered by case 10
TEST(Unit_u1508, TC10_CallsTarget) {
  Solver::Options options{};
  ceres::TrustRegionOptionsAreValid(options, nullptr);
}

// P11: START -> 1 -> END; branch decisions covered by case 11
TEST(Unit_u1508, TC11_CallsTarget) {
  Solver::Options options{};
  ceres::TrustRegionOptionsAreValid(options, nullptr);
}

// P12: START -> 1 -> END; branch decisions covered by case 12
TEST(Unit_u1508, TC12_CallsTarget) {
  Solver::Options options{};
  ceres::TrustRegionOptionsAreValid(options, nullptr);
}

// P13: START -> 1 -> END; branch decisions covered by case 13
TEST(Unit_u1508, TC13_CallsTarget) {
  Solver::Options options{};
  ceres::TrustRegionOptionsAreValid(options, nullptr);
}

// P14: START -> 1 -> END; branch decisions covered by case 14
TEST(Unit_u1508, TC14_CallsTarget) {
  Solver::Options options{};
  ceres::TrustRegionOptionsAreValid(options, nullptr);
}

// P15: START -> 1 -> END; branch decisions covered by case 15
TEST(Unit_u1508, TC15_CallsTarget) {
  Solver::Options options{};
  ceres::TrustRegionOptionsAreValid(options, nullptr);
}

// P16: START -> 1 -> END; branch decisions covered by case 16
TEST(Unit_u1508, TC16_CallsTarget) {
  Solver::Options options{};
  ceres::TrustRegionOptionsAreValid(options, nullptr);
}

// P17: START -> 1 -> END; branch decisions covered by case 17
TEST(Unit_u1508, TC17_CallsTarget) {
  Solver::Options options{};
  ceres::TrustRegionOptionsAreValid(options, nullptr);
}

// P18: START -> 1 -> END; branch decisions covered by case 18
TEST(Unit_u1508, TC18_CallsTarget) {
  Solver::Options options{};
  ceres::TrustRegionOptionsAreValid(options, nullptr);
}

// P19: START -> 1 -> END; branch decisions covered by case 19
TEST(Unit_u1508, TC19_CallsTarget) {
  Solver::Options options{};
  ceres::TrustRegionOptionsAreValid(options, nullptr);
}

// P20: START -> 1 -> END; branch decisions covered by case 20
TEST(Unit_u1508, TC20_CallsTarget) {
  Solver::Options options{};
  ceres::TrustRegionOptionsAreValid(options, nullptr);
}

// P21: START -> 1 -> END; branch decisions covered by case 21
TEST(Unit_u1508, TC21_CallsTarget) {
  Solver::Options options{};
  ceres::TrustRegionOptionsAreValid(options, nullptr);
}

// P22: START -> 1 -> END; branch decisions covered by case 22
TEST(Unit_u1508, TC22_CallsTarget) {
  Solver::Options options{};
  ceres::TrustRegionOptionsAreValid(options, nullptr);
}

// P23: START -> 1 -> END; branch decisions covered by case 23
TEST(Unit_u1508, TC23_CallsTarget) {
  Solver::Options options{};
  ceres::TrustRegionOptionsAreValid(options, nullptr);
}
```
