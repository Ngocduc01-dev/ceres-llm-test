**A. Test paths**

Unit không có điểm rẽ nhánh nào (0 điểm rẽ nhánh, tổng 0 nhánh). CFG chỉ có một đường đi duy nhất. CFG khớp với mã nguồn.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh nào (không có điểm rẽ nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `a` là số thực bất kỳ (không có điều kiện ràng buộc), chọn trong [0.1, 5.0] | `a = 2.5` |

**C. Nhánh không test**

Không có nhánh nào bị bỏ qua.

C2 dự kiến = 0 / 0 (không có điểm rẽ nhánh; toàn bộ node 1 được thực thi bởi TC1, tức phủ 100% câu lệnh).

**D. File test**

```cpp
// FILE: u0172_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(HuberLossConstructor, TC1_SinglePath) {
  ceres::HuberLoss loss(2.5);
  (void)loss;
}
```