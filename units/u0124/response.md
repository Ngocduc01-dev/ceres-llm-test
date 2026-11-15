**A. Test paths**

Hàm `erf` không có điểm rẽ nhánh nào (CFG khớp mã nguồn: chỉ có node 1, gồm câu lệnh `return` với phép `operator*`). Chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh (0 điểm rẽ nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `x.a` là số thực bất kỳ; `x.v` là vector 2 phần tử bất kỳ (`Jet<double, 2>`) | `x.a = 0.37`, `x.v = (0.52, -0.81)` |

**C. Nhánh không test**

Không có nhánh nào bị bỏ qua (hàm không có điểm rẽ nhánh, nên không có nhánh `CHECK` hay nhánh không thể đi tới).

`C2 dự kiến = 0 / 0` (tổng số nhánh = 0, nên C2 coi như đạt toàn bộ khi P1 được chạy qua).

**D. File test**

```cpp
// FILE: u0124_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetErfTest, SinglePathNoBranch) {
  using JetType = ceres::Jet<double, 2>;
  JetType x(0.37);
  x.v[0] = 0.52;
  x.v[1] = -0.81;
  JetType result = erf(x);
  (void)result;
}
```