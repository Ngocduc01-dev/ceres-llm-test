**A. Test paths**

Unit không có điểm rẽ nhánh nào (0 điểm) nên chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `a` là số thực bất kỳ, chọn trong (0, 10] vì không có điều kiện đường đi | `a = 3.7` (cố định) |

**C. Nhánh không test**

Không có. Unit không có điểm rẽ nhánh nào và không có `CHECK`.

`C2 dự kiến = 0 / 0 (không có nhánh nào cần phủ; node 1 được chạy qua nên đạt 100%)`

**D. File test**

```cpp
// FILE: u0173_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(SoftLOneLossConstructorTest, TC1_P1_SingleStraightPath) {
  const double a = 3.7;  // giá trị cố định trong khoảng (0, 10]
  ceres::SoftLOneLoss loss(a);
  (void)loss;  // không kiểm tra kết quả
}
```