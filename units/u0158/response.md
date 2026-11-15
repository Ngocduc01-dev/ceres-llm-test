**A. Test paths**

Hàm không có điểm rẽ nhánh (không có `if`, vòng lặp, `switch`, `?:`).

CFG: `START → 1 → END`
- Node 1: `return ceres::Jet<T, N>(std::numeric_limits<T>::denorm_min());`

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Hàm không có tham số. Tham số template: T là kiểu số thực, N từ 1 đến 5 | T = `double`, N = 2 (chọn cố định) |

**C. Nhánh không test**

Không có nhánh nào bị bỏ. Hàm không có điểm rẽ nhánh nên tổng số nhánh là 0, và `CHECK` cũng không có.

C2 dự kiến = 0 / 0 (không có nhánh nào cần phủ; TC1 chạy qua toàn bộ node 1, tức đạt 100% câu lệnh)

**D. File test**

```cpp
// FILE: u0158_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(NumericLimitsJetDenormMin, P1_StraightLine) {
  std::numeric_limits<ceres::Jet<double, 2>> obj;
  auto result = obj.denorm_min();
  (void)result;
}
```