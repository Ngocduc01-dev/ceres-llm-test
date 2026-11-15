**A. Test paths**

Unit chỉ có một lệnh `return`, không có điểm rẽ nhánh. CFG: `START → 1 → END`, trong đó node 1 là `return Real((std::numeric_limits<T>::max)());`.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có tham số đầu vào. Chỉ chọn kiểu template: `T` là kiểu số thực, `N ≥ 1`. | `T = double`, `N = 2` |

**C. Nhánh không test**

Không có nhánh nào, vì unit không có điểm rẽ nhánh và không có `CHECK`.

`C2 dự kiến = 0 / 0` (tổng số nhánh là 0; đường đi duy nhất P1 được chạy qua nên coi như đạt 100%).

**D. File test**

```cpp
// FILE: u0164_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(NumTraitsJetHighest, TC1_P1_ReturnHighest) {
  Eigen::NumTraits<ceres::Jet<double, 2>> obj;
  obj.highest();
}
```