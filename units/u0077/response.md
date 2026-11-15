**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm rẽ nhánh, 0 nhánh, không có vòng lặp, không có `CHECK`). CFG khớp với mã nguồn. Chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh nào (không có điểm rẽ nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f.a` là double bất kỳ; `f.v` là vector 10 phần tử double bất kỳ (không có điều kiện ràng buộc) | `f.a = 3.5`; `f.v` = {1.5, -2.0, 0.5, 4.0, -1.0, 2.5, -3.5, 0.0, 1.0, -0.5} |

**C. Nhánh không test**

Không có nhánh nào (tổng số nhánh = 0). Node 1 được chạy qua bởi TC1.

`C2 dự kiến = 0 / 0` (không có nhánh; toàn bộ node và đường đi duy nhất P1 đã được phủ, tương đương 100%).

**D. File test**

```cpp
// FILE: u0077_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetUnaryMinusTest, P1_NegateJet) {
  Jet<double, 10> f;
  f.a = 3.5;
  const double values[10] = {1.5, -2.0, 0.5, 4.0, -1.0,
                             2.5, -3.5, 0.0, 1.0, -0.5};
  for (int i = 0; i < 10; ++i) {
    f.v[i] = values[i];
  }

  Jet<double, 10> g = -f;
  (void)g;
}

}  // namespace internal
}  // namespace ceres
```