**A. Test paths**

Hàm không có điểm rẽ nhánh (0 điểm rẽ nhánh, 0 nhánh). Chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f.a`, `g.a` là double sao cho `f.a² + g.a² ≠ 0` (ví dụ f.a ∈ [1, 5], g.a ∈ [1, 5]); `f.v`, `g.v` là vector 8 phần tử, mỗi phần tử ∈ [-5, 5] | f.a = 3.0, g.a = 2.0; f.v = {1, -2, 3, 0.5, -1.5, 4, -3, 2}; g.v = {-1, 2, 0.5, 3, -4, 1, 2.5, -0.5} |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh nên không có nhánh nào cần phủ, và không có nhánh `CHECK`.

C2 dự kiến = 0 / 0 (không có nhánh nào; toàn bộ hàm được thực thi bởi TC1, tức phủ câu lệnh 100%).

Ghi chú: CFG khớp với mã nguồn. Dòng `return` (dòng 1138) nằm cùng node 1 vì không có rẽ nhánh.

**D. File test**

```cpp
// FILE: u0148_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetAtan2Test, TC1_SingleStraightPath) {
  using JetT = Jet<double, 8>;

  JetT f;
  JetT g;
  f.a = 3.0;
  g.a = 2.0;

  const double fv[8] = {1.0, -2.0, 3.0, 0.5, -1.5, 4.0, -3.0, 2.0};
  const double gv[8] = {-1.0, 2.0, 0.5, 3.0, -4.0, 1.0, 2.5, -0.5};
  for (int i = 0; i < 8; ++i) {
    f.v[i] = fv[i];
    g.v[i] = gv[i];
  }

  JetT result = atan2(g, f);
  (void)result;
}

}  // namespace internal
}  // namespace ceres
```