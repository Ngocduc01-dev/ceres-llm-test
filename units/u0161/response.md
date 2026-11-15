**CFG:** `START → node 1 (dòng 1379: return Real(std::numeric_limits<T>::epsilon())) → END`

Unit không có điểm rẽ nhánh nào, nên tổng số nhánh là 0.

**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Hàm không có tham số. Kiểu template: `Jet<T, N>` với `T = double`, `N` từ 1 đến 5 | `NumTraits<Jet<double, 2>>` |

**C. Nhánh không test**

Không có nhánh nào, và cũng không có `CHECK` hay vòng lặp.

`C2 dự kiến = 0 / 0` (không có nhánh nào, coi như đạt 100%; path P1 phủ toàn bộ câu lệnh duy nhất).

**D. File test**

```cpp
// FILE: u0161_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(NumTraitsEpsilon, TC1_P1_JetDoubleN2) {
  Eigen::NumTraits<ceres::Jet<double, 2>> obj;
  (void)obj.epsilon();
}
```