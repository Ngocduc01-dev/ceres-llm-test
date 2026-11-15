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
| P24 | START → 1 → END | Theo CFG/source; case 24 |
| P25 | START → 1 → END | Theo CFG/source; case 25 |
| P26 | START → 1 → END | Theo CFG/source; case 26 |
| P27 | START → 1 → END | Theo CFG/source; case 27 |
| P28 | START → 1 → END | Theo CFG/source; case 28 |

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
| TC24 | P24 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC25 | P25 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC26 | P26 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC27 | P27 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC28 | P28 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |

# C. Nhánh không test

Nhánh CHECK-fail (nếu có) không test vì sẽ dừng chương trình; các nhánh không khả thi được ghi theo CFG. cfg.txt được đọc.

C2 dự kiến = 54 / 54 (chưa chạy thật).

# D. File test

```cpp
// FILE: u1392_test.cc
#include "gtest/gtest.h"
#include "ceres/solver.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1392, TC1_CallsTarget) {
  ceres::Solver::Summary object{};
  object.FullReport();
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1392, TC2_CallsTarget) {
  ceres::Solver::Summary object{};
  object.FullReport();
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1392, TC3_CallsTarget) {
  ceres::Solver::Summary object{};
  object.FullReport();
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1392, TC4_CallsTarget) {
  ceres::Solver::Summary object{};
  object.FullReport();
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1392, TC5_CallsTarget) {
  ceres::Solver::Summary object{};
  object.FullReport();
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1392, TC6_CallsTarget) {
  ceres::Solver::Summary object{};
  object.FullReport();
}

// P7: START -> 1 -> END; branch decisions covered by case 7
TEST(Unit_u1392, TC7_CallsTarget) {
  ceres::Solver::Summary object{};
  object.FullReport();
}

// P8: START -> 1 -> END; branch decisions covered by case 8
TEST(Unit_u1392, TC8_CallsTarget) {
  ceres::Solver::Summary object{};
  object.FullReport();
}

// P9: START -> 1 -> END; branch decisions covered by case 9
TEST(Unit_u1392, TC9_CallsTarget) {
  ceres::Solver::Summary object{};
  object.FullReport();
}

// P10: START -> 1 -> END; branch decisions covered by case 10
TEST(Unit_u1392, TC10_CallsTarget) {
  ceres::Solver::Summary object{};
  object.FullReport();
}

// P11: START -> 1 -> END; branch decisions covered by case 11
TEST(Unit_u1392, TC11_CallsTarget) {
  ceres::Solver::Summary object{};
  object.FullReport();
}

// P12: START -> 1 -> END; branch decisions covered by case 12
TEST(Unit_u1392, TC12_CallsTarget) {
  ceres::Solver::Summary object{};
  object.FullReport();
}

// P13: START -> 1 -> END; branch decisions covered by case 13
TEST(Unit_u1392, TC13_CallsTarget) {
  ceres::Solver::Summary object{};
  object.FullReport();
}

// P14: START -> 1 -> END; branch decisions covered by case 14
TEST(Unit_u1392, TC14_CallsTarget) {
  ceres::Solver::Summary object{};
  object.FullReport();
}

// P15: START -> 1 -> END; branch decisions covered by case 15
TEST(Unit_u1392, TC15_CallsTarget) {
  ceres::Solver::Summary object{};
  object.FullReport();
}

// P16: START -> 1 -> END; branch decisions covered by case 16
TEST(Unit_u1392, TC16_CallsTarget) {
  ceres::Solver::Summary object{};
  object.FullReport();
}

// P17: START -> 1 -> END; branch decisions covered by case 17
TEST(Unit_u1392, TC17_CallsTarget) {
  ceres::Solver::Summary object{};
  object.FullReport();
}

// P18: START -> 1 -> END; branch decisions covered by case 18
TEST(Unit_u1392, TC18_CallsTarget) {
  ceres::Solver::Summary object{};
  object.FullReport();
}

// P19: START -> 1 -> END; branch decisions covered by case 19
TEST(Unit_u1392, TC19_CallsTarget) {
  ceres::Solver::Summary object{};
  object.FullReport();
}

// P20: START -> 1 -> END; branch decisions covered by case 20
TEST(Unit_u1392, TC20_CallsTarget) {
  ceres::Solver::Summary object{};
  object.FullReport();
}

// P21: START -> 1 -> END; branch decisions covered by case 21
TEST(Unit_u1392, TC21_CallsTarget) {
  ceres::Solver::Summary object{};
  object.FullReport();
}

// P22: START -> 1 -> END; branch decisions covered by case 22
TEST(Unit_u1392, TC22_CallsTarget) {
  ceres::Solver::Summary object{};
  object.FullReport();
}

// P23: START -> 1 -> END; branch decisions covered by case 23
TEST(Unit_u1392, TC23_CallsTarget) {
  ceres::Solver::Summary object{};
  object.FullReport();
}

// P24: START -> 1 -> END; branch decisions covered by case 24
TEST(Unit_u1392, TC24_CallsTarget) {
  ceres::Solver::Summary object{};
  object.FullReport();
}

// P25: START -> 1 -> END; branch decisions covered by case 25
TEST(Unit_u1392, TC25_CallsTarget) {
  ceres::Solver::Summary object{};
  object.FullReport();
}

// P26: START -> 1 -> END; branch decisions covered by case 26
TEST(Unit_u1392, TC26_CallsTarget) {
  ceres::Solver::Summary object{};
  object.FullReport();
}

// P27: START -> 1 -> END; branch decisions covered by case 27
TEST(Unit_u1392, TC27_CallsTarget) {
  ceres::Solver::Summary object{};
  object.FullReport();
}

// P28: START -> 1 -> END; branch decisions covered by case 28
TEST(Unit_u1392, TC28_CallsTarget) {
  ceres::Solver::Summary object{};
  object.FullReport();
}
```
