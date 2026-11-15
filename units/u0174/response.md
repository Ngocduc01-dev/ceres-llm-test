**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh (0 nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `a` là số thực khác 0 (để `a*a` ≠ 0, tránh 1/0), ví dụ từ 0.5 đến 5.0 | `a = 2.0` |

**C. Nhánh không test**

Không có. Unit không có điểm rẽ nhánh nên tổng số nhánh = 0; chỉ có một đường đi duy nhất (node 1). CFG khớp với mã nguồn.

C2 dự kiến = 0 / 0 (không có nhánh nào; node 1 được chạy qua bởi TC1, nên độ phủ câu lệnh 100%).

**D. File test**

```cpp
// FILE: u0174_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

// Path P1: START -> 1 -> END
TEST(CauchyLossConstructorTest, P1_SingleStraightPath) {
  ceres::CauchyLoss loss(2.0);
}
```