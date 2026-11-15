**A. Test paths**

CFG: `START → 1 → END`. Node 1 chứa `return ceres::Jet<T, N>(std::numeric_limits<T>::epsilon());`. Hàm không có điểm rẽ nhánh nên tổng số nhánh là 0.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Hàm không có tham số. Kiểu `T` và `N` được chọn khi tạo object: `T` là kiểu số thực, `N` từ 1 đến 5 | `T = double`, `N = 2` |

**C. Nhánh không test**

Không có nhánh nào, vì hàm không có điểm rẽ nhánh và cũng không có `CHECK`.

`C2 dự kiến = 0 / 0 (không có nhánh nào, path P1 được chạy hết, coi như đạt 100%)`

**D. File test**

```cpp
// FILE: u0153_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(NumericLimitsJetEpsilon, TC1_P1_Epsilon) {
  std::numeric_limits<ceres::Jet<double, 2>> obj;
  auto result = obj.epsilon();
  static_cast<void>(result);
}
```