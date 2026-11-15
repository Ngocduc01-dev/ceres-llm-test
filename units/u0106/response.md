**A. Test paths**

Hàm `sqrt` không có điểm rẽ nhánh (0 điểm rẽ nhánh, 0 nhánh). Mã nguồn khớp với CFG (dòng 606 `return` nằm cùng node 1).

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh nào (đường đi duy nhất) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f.a` trong (0, 100]; `f.v` là vector 7 phần tử, mỗi phần tử trong [-10, 10]; không có điều kiện ràng buộc nào khác | `f.a = 6.0`; `f.v = {3.0, -7.0, 1.0, 9.0, -2.0, 5.0, 8.0}` |

**C. Nhánh không test**

Không có nhánh nào (hàm không có điểm rẽ nhánh). Không có vòng lặp. Không có `CHECK`.
`C2 dự kiến = 0 / 0` (tổng số nhánh bằng 0; mọi câu lệnh đều chạy qua khi gọi hàm 1 lần, nên coi như phủ đầy đủ).

**D. File test**

```cpp
// FILE: u0106_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (hàm không có điểm rẽ nhánh)
TEST(JetSqrtTest, TC1_P1_SinglePath) {
  Jet<double, 7> f;
  f.a = 6.0;
  f.v[0] = 3.0;
  f.v[1] = -7.0;
  f.v[2] = 1.0;
  f.v[3] = 9.0;
  f.v[4] = -2.0;
  f.v[5] = 5.0;
  f.v[6] = 8.0;

  Jet<double, 7> r = sqrt(f);
  (void)r;
}

}  // namespace internal
}  // namespace ceres
```