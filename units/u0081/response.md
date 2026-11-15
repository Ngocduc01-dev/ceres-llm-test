**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm rẽ nhánh, 0 nhánh). CFG khớp với mã nguồn (dòng 332 là một lệnh `return` duy nhất).

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f.a`, `g.a` ∈ [-10, 10]; `f.v`, `g.v` là vector 4 phần tử, mỗi phần tử ∈ [-10, 10] (không có điều kiện ràng buộc) | `f.a = 3.0`, `f.v = (1, -2, 5, 7)`; `g.a = -4.0`, `g.v = (6, 2, -3, 9)` (chọn cố định, đại diện cho lựa chọn ngẫu nhiên với seed cố định) |

**C. Nhánh không test**

Không có nhánh nào (tổng số nhánh = 0, không có nhánh không thể đi tới và không có `CHECK`).

`C2 dự kiến = 0 / 0` (không có nhánh; hàm được phủ hoàn toàn bằng 1 test đi qua node 1, tương ứng 100%).

**D. File test**

```cpp
// FILE: u0081_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetOperatorMinus, TC1_BinarySubtraction) {
  using JetT = ceres::Jet<double, 4>;

  JetT f;
  f.a = 3.0;
  f.v[0] = 1.0;
  f.v[1] = -2.0;
  f.v[2] = 5.0;
  f.v[3] = 7.0;

  JetT g;
  g.a = -4.0;
  g.v[0] = 6.0;
  g.v[1] = 2.0;
  g.v[2] = -3.0;
  g.v[3] = 9.0;

  JetT h = f - g;
  (void)h;
}
```