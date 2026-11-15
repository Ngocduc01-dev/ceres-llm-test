**A. Test paths**

Hàm không có điểm rẽ nhánh nào (CFG chỉ có node 1), nên chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Jet<double, 2> a: giá trị thực bất kỳ, a = Jet(value, k) với k trong {0, 1}; s: double bất kỳ (không có điều kiện ràng buộc) | a = Jet<double, 2>(3.0, 0); s = 2.0 |

**C. Nhánh không test**

Không có nhánh nào (0 điểm rẽ nhánh, không có nhánh `CHECK`).
Lưu ý: CFG khớp với mã nguồn (dòng 276–277).

`C2 dự kiến = 0 / 0` (không có nhánh; test đi qua toàn bộ node 1 nên coi như 100%).

**D. File test**

```cpp
// FILE: u0074_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetOperatorMulAssignScalarTest, P1_MultiplyAssignByScalar) {
  ceres::Jet<double, 2> a(3.0, 0);
  const double s = 2.0;
  a *= s;
}
```