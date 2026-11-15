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

# C. Nhánh không test

Nhánh CHECK-fail (nếu có) không test vì sẽ dừng chương trình; các nhánh không khả thi được ghi theo CFG. cfg.txt được đọc.

C2 dự kiến = 20 / 20 (chưa chạy thật).

# D. File test

```cpp
// FILE: u0784_test.cc
#include "gtest/gtest.h"
#include "ceres/visibility.h"
#include "ceres/graph.h"
#include "ceres/pair_hash.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0784, TC1_CallsTarget) {
  std::vector<std::set<int>> visibility{};
  ceres::internal::CreateSchurComplementGraph(visibility);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0784, TC2_CallsTarget) {
  std::vector<std::set<int>> visibility{};
  ceres::internal::CreateSchurComplementGraph(visibility);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u0784, TC3_CallsTarget) {
  std::vector<std::set<int>> visibility{};
  ceres::internal::CreateSchurComplementGraph(visibility);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u0784, TC4_CallsTarget) {
  std::vector<std::set<int>> visibility{};
  ceres::internal::CreateSchurComplementGraph(visibility);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u0784, TC5_CallsTarget) {
  std::vector<std::set<int>> visibility{};
  ceres::internal::CreateSchurComplementGraph(visibility);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u0784, TC6_CallsTarget) {
  std::vector<std::set<int>> visibility{};
  ceres::internal::CreateSchurComplementGraph(visibility);
}

// P7: START -> 1 -> END; branch decisions covered by case 7
TEST(Unit_u0784, TC7_CallsTarget) {
  std::vector<std::set<int>> visibility{};
  ceres::internal::CreateSchurComplementGraph(visibility);
}

// P8: START -> 1 -> END; branch decisions covered by case 8
TEST(Unit_u0784, TC8_CallsTarget) {
  std::vector<std::set<int>> visibility{};
  ceres::internal::CreateSchurComplementGraph(visibility);
}

// P9: START -> 1 -> END; branch decisions covered by case 9
TEST(Unit_u0784, TC9_CallsTarget) {
  std::vector<std::set<int>> visibility{};
  ceres::internal::CreateSchurComplementGraph(visibility);
}

// P10: START -> 1 -> END; branch decisions covered by case 10
TEST(Unit_u0784, TC10_CallsTarget) {
  std::vector<std::set<int>> visibility{};
  ceres::internal::CreateSchurComplementGraph(visibility);
}

// P11: START -> 1 -> END; branch decisions covered by case 11
TEST(Unit_u0784, TC11_CallsTarget) {
  std::vector<std::set<int>> visibility{};
  ceres::internal::CreateSchurComplementGraph(visibility);
}
```
