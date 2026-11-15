**A. Test paths**

Hàm không có điểm rẽ nhánh (CFG khớp mã nguồn: một node duy nhất), nên chỉ có 1 đường đi.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f.a` ∈ [-10, 10]; `f.v` (4 phần tử) ∈ [-10, 10]; `s` ∈ [-10, 10] (không có ràng buộc từ đường đi) | `f.a` = 3.5; `f.v` = {1.25, -2.0, 4.5, 0.75}; `s` = -6.25 |

**C. Nhánh không test**

Không có nhánh nào (0 điểm rẽ nhánh, không có nhánh `CHECK`).

`C2 dự kiến = 0 / 0` (không có nhánh nào; toàn bộ câu lệnh ở node 1 được chạy bởi TC1, tức C1 = 100%).

**D. File test**

```cpp
// FILE: u0079_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetOperatorPlusScalarRight, P1_SingleStatement) {
  Jet<double, 4> f;
  f.a = 3.5;
  f.v[0] = 1.25;
  f.v[1] = -2.0;
  f.v[2] = 4.5;
  f.v[3] = 0.75;
  const double s = -6.25;

  Jet<double, 4> r = operator+(f, s);
  (void)r;
}

}  // namespace internal
}  // namespace ceres
```