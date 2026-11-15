**A. Test paths**

Hàm không có điểm rẽ nhánh nên chỉ có một đường đi duy nhất. Không có vòng lặp.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `x.a`, `y.a`, `z.a` ∈ (0, 5] để `tmp = hypot(...)` > 0, tránh chia cho 0. Thành phần đạo hàm: `Jet(value, k)` với k ∈ [0, 11]. | `x = Jet<double,12>(1.5, 0)`, `y = Jet<double,12>(2.0, 1)`, `z = Jet<double,12>(2.5, 2)` |

**C. Nhánh không test**

Không có nhánh nào bị bỏ qua: hàm không có điểm rẽ nhánh và không có `CHECK`.

C2 dự kiến = 0 / 0 (tổng số nhánh bằng 0, đường đi duy nhất P1 được chạy qua nên coi như đạt 100%).

**D. File test**

```cpp
// FILE: u0122_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (hàm không có điểm rẽ nhánh)
TEST(JetHypot3Test, TC1_SingleStraightLinePath) {
  const Jet<double, 12> x(1.5, 0);
  const Jet<double, 12> y(2.0, 1);
  const Jet<double, 12> z(2.5, 2);

  const Jet<double, 12> r = hypot(x, y, z);
  (void)r;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
```