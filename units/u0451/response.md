**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → END | node 1: đúng (`fpclassify(g) == FP_ZERO`) |
| P2 | START → 1 → 2 → END | node 1: sai (`fpclassify(g) != FP_ZERO`) |

Ghi chú: mã nguồn khớp với CFG. Hàm không có vòng lặp và không có `CHECK`.

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `g.a == 0.0`; `f.a` ∈ [-5, 5] và khác 0; `f.v`, `g.v` ∈ [-5, 5] | `f.a = 2.5`, `f.v = {1.5, -3.0}`; `g.a = 0.0`, `g.v = {4.0, 0.5}` |
| TC2 | P2 | `g.a ≠ 0`, `g.a` ∈ [-5, 5]; `f.a` ∈ [-5, 5]; `f.v`, `g.v` ∈ [-5, 5] | `f.a = 3.25`, `f.v = {-2.0, 1.0}`; `g.a = -1.75`, `g.v = {0.75, 2.5}` |

Các giá trị được chọn cố định trong code, nên mỗi lần chạy cho cùng một kết quả.

**C. Nhánh không test**

Không có nhánh nào bị bỏ. Không có nhánh không thể đi tới và không có nhánh `CHECK`.

`C2 dự kiến = 2 / 2`

**D. File test**

```cpp
// FILE: u0451_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// Path P1: node 1: đúng (g.a == 0) -> node 2 -> END
TEST(JetCopysignCft, GaIsZero) {
  Jet<double, 2> f(2.5);
  f.v[0] = 1.5;
  f.v[1] = -3.0;
  Jet<double, 2> g(0.0);
  g.v[0] = 4.0;
  g.v[1] = 0.5;
  Jet<double, 2> r = ceres::copysign(f, g);
  (void)r;
}

// Path P2: node 1: sai (g.a != 0) -> node 2 -> END
TEST(JetCopysignCft, GaIsNonZero) {
  Jet<double, 2> f(3.25);
  f.v[0] = -2.0;
  f.v[1] = 1.0;
  Jet<double, 2> g(-1.75);
  g.v[0] = 0.75;
  g.v[1] = 2.5;
  Jet<double, 2> r = ceres::copysign(f, g);
  (void)r;
}

}  // namespace internal
}  // namespace ceres
```