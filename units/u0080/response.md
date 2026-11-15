**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm rẽ nhánh, 0 vòng lặp, 0 `CHECK`). Chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh nào (node 1 là câu lệnh `return`) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `s` ∈ [-10, 10] (double); `f.a` ∈ [-10, 10]; `f.v` là vector 4 phần tử, mỗi phần tử ∈ [-10, 10] | `s` = 3.5; `f.a` = -2.0; `f.v` = {1.5, -4.0, 0.5, 7.0} |

**C. Nhánh không test**

Không có nhánh nào bị bỏ qua. Hàm không có điểm rẽ nhánh nên không có nhánh để loại trừ.

`C2 dự kiến = 0 / 0` (tổng số nhánh = 0; coi như đạt 100% vì đường đi duy nhất đã được chạy qua).

**D. File test**

```cpp
// FILE: u0080_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetOperatorPlusScalarLeft, SinglePath) {
  Jet<double, 4> f;
  f.a = -2.0;
  f.v[0] = 1.5;
  f.v[1] = -4.0;
  f.v[2] = 0.5;
  f.v[3] = 7.0;

  const double s = 3.5;
  Jet<double, 4> r = s + f;
  (void)r;
}

}  // namespace internal
}  // namespace ceres
```