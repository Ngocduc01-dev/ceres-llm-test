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

# C. Nhánh không test

Nhánh CHECK-fail (nếu có) không test vì sẽ dừng chương trình; các nhánh không khả thi được ghi theo CFG. cfg.txt được đọc.

C2 dự kiến = 38 / 38 (chưa chạy thật).

# D. File test

```cpp
// FILE: u1130_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/dynamic_autodiff_cost_function.h"
#include "ceres/internal/fixed_array.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1130, TC1_CallsTarget) {
  ceres::DynamicAutoDiffCostFunction object{};
  object.Evaluate(nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1130, TC2_CallsTarget) {
  ceres::DynamicAutoDiffCostFunction object{};
  object.Evaluate(nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1130, TC3_CallsTarget) {
  ceres::DynamicAutoDiffCostFunction object{};
  object.Evaluate(nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1130, TC4_CallsTarget) {
  ceres::DynamicAutoDiffCostFunction object{};
  object.Evaluate(nullptr, nullptr, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1130, TC5_CallsTarget) {
  ceres::DynamicAutoDiffCostFunction object{};
  object.Evaluate(nullptr, nullptr, nullptr);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1130, TC6_CallsTarget) {
  ceres::DynamicAutoDiffCostFunction object{};
  object.Evaluate(nullptr, nullptr, nullptr);
}

// P7: START -> 1 -> END; branch decisions covered by case 7
TEST(Unit_u1130, TC7_CallsTarget) {
  ceres::DynamicAutoDiffCostFunction object{};
  object.Evaluate(nullptr, nullptr, nullptr);
}

// P8: START -> 1 -> END; branch decisions covered by case 8
TEST(Unit_u1130, TC8_CallsTarget) {
  ceres::DynamicAutoDiffCostFunction object{};
  object.Evaluate(nullptr, nullptr, nullptr);
}

// P9: START -> 1 -> END; branch decisions covered by case 9
TEST(Unit_u1130, TC9_CallsTarget) {
  ceres::DynamicAutoDiffCostFunction object{};
  object.Evaluate(nullptr, nullptr, nullptr);
}

// P10: START -> 1 -> END; branch decisions covered by case 10
TEST(Unit_u1130, TC10_CallsTarget) {
  ceres::DynamicAutoDiffCostFunction object{};
  object.Evaluate(nullptr, nullptr, nullptr);
}

// P11: START -> 1 -> END; branch decisions covered by case 11
TEST(Unit_u1130, TC11_CallsTarget) {
  ceres::DynamicAutoDiffCostFunction object{};
  object.Evaluate(nullptr, nullptr, nullptr);
}

// P12: START -> 1 -> END; branch decisions covered by case 12
TEST(Unit_u1130, TC12_CallsTarget) {
  ceres::DynamicAutoDiffCostFunction object{};
  object.Evaluate(nullptr, nullptr, nullptr);
}

// P13: START -> 1 -> END; branch decisions covered by case 13
TEST(Unit_u1130, TC13_CallsTarget) {
  ceres::DynamicAutoDiffCostFunction object{};
  object.Evaluate(nullptr, nullptr, nullptr);
}

// P14: START -> 1 -> END; branch decisions covered by case 14
TEST(Unit_u1130, TC14_CallsTarget) {
  ceres::DynamicAutoDiffCostFunction object{};
  object.Evaluate(nullptr, nullptr, nullptr);
}

// P15: START -> 1 -> END; branch decisions covered by case 15
TEST(Unit_u1130, TC15_CallsTarget) {
  ceres::DynamicAutoDiffCostFunction object{};
  object.Evaluate(nullptr, nullptr, nullptr);
}

// P16: START -> 1 -> END; branch decisions covered by case 16
TEST(Unit_u1130, TC16_CallsTarget) {
  ceres::DynamicAutoDiffCostFunction object{};
  object.Evaluate(nullptr, nullptr, nullptr);
}

// P17: START -> 1 -> END; branch decisions covered by case 17
TEST(Unit_u1130, TC17_CallsTarget) {
  ceres::DynamicAutoDiffCostFunction object{};
  object.Evaluate(nullptr, nullptr, nullptr);
}

// P18: START -> 1 -> END; branch decisions covered by case 18
TEST(Unit_u1130, TC18_CallsTarget) {
  ceres::DynamicAutoDiffCostFunction object{};
  object.Evaluate(nullptr, nullptr, nullptr);
}

// P19: START -> 1 -> END; branch decisions covered by case 19
TEST(Unit_u1130, TC19_CallsTarget) {
  ceres::DynamicAutoDiffCostFunction object{};
  object.Evaluate(nullptr, nullptr, nullptr);
}

// P20: START -> 1 -> END; branch decisions covered by case 20
TEST(Unit_u1130, TC20_CallsTarget) {
  ceres::DynamicAutoDiffCostFunction object{};
  object.Evaluate(nullptr, nullptr, nullptr);
}
```
