**A. Test paths**

Hàm không có điểm rẽ nhánh (0 điểm rẽ nhánh, 0 nhánh, không có vòng lặp), nên chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh nào (không có điểm rẽ nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f.a`, `g.a` là số thực bất kỳ; `f.v`, `g.v` là vector 4 phần tử số thực bất kỳ (không có điều kiện ràng buộc). Chọn trong [-5, 5], seed cố định 42 | `f.a = 1.5`, `g.a = -2.0`, `f.v = {0.5, -1.0, 2.0, 3.5}`, `g.v = {-0.5, 1.0, 4.0, -3.0}` (cố định sẵn, đã chọn trong khoảng, không dùng hàm sinh số ngẫu nhiên) |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh nên không có nhánh nào cần phủ và không có `CHECK`.

Ghi chú: CFG khớp với mã nguồn.

`C2 dự kiến = 0 / 0` (không có nhánh; test duy nhất chạy hết node 1, tức phủ toàn bộ câu lệnh, nên coi như đạt 100%).

**D. File test**

```cpp
// FILE: u0084_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetOperatorMultiplyTest, TC1_JetTimesJet) {
  Jet<double, 4> f;
  f.a = 1.5;
  f.v[0] = 0.5;
  f.v[1] = -1.0;
  f.v[2] = 2.0;
  f.v[3] = 3.5;

  Jet<double, 4> g;
  g.a = -2.0;
  g.v[0] = -0.5;
  g.v[1] = 1.0;
  g.v[2] = 4.0;
  g.v[3] = -3.0;

  Jet<double, 4> h = f * g;
  (void)h;
}

}  // namespace
}  // namespace ceres
```