**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm rẽ nhánh, tổng số nhánh = 0). CFG khớp với mã nguồn: hai initializer (base `LossFunction()` và `a_squared_(a * a)`) chạy liền nhau trong node 1. Không có vòng lặp và không có `CHECK`.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh rẽ nào (đường đi duy nhất) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `a` là số thực bất kỳ, không có ràng buộc từ điều kiện đường đi; chọn trong [0.5, 5.0] | `a = 2.7` (số cố định, đại diện cho giá trị ngẫu nhiên trong khoảng) |

**C. Nhánh không test**

Không có nhánh nào bị bỏ qua (unit không có điểm rẽ nhánh, không có vòng lặp, không có `CHECK`).

`C2 dự kiến = 0 / 0` (không có nhánh nào; path P1 phủ toàn bộ node 1, tức đạt 100% theo quy ước).

**D. File test**

```cpp
// FILE: u0176_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(TukeyLossConstructorTest, TC1_P1_SinglePath) {
  ceres::TukeyLoss loss(2.7);
  (void)loss;
}
```