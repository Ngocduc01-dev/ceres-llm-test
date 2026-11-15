**A. Test paths**

Hàm không có điểm rẽ nhánh (0 điểm rẽ nhánh), nên chỉ có một đường đi duy nhất. CFG khớp với mã nguồn: node 1 chứa cả lệnh `hypot(x.a, y.a)` và lệnh `return`.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh (0 điểm rẽ nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `x.a`, `y.a` ∈ [1, 5] (tránh `tmp = 0` gây chia cho 0); `x.v`, `y.v` là vector 2 phần tử, mỗi phần tử ∈ [1, 5] | `x.a = 3`, `y.a = 4`, `x.v = (1, 2)`, `y.v = (5, 3)` (cố định, không dùng số ngẫu nhiên) |

**C. Nhánh không test**

Không có nhánh nào (hàm không có điểm rẽ nhánh, không có `CHECK`).

`C2 dự kiến = 0 / 0` (không có nhánh; hàm được phủ toàn bộ bởi 1 test đi qua node 1, tức 100%).

**D. File test**

```cpp
// FILE: u0121_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetHypot, P1_SingleStraightPath) {
  using JetT = Jet<double, 2>;

  JetT x(3.0);
  x.v[0] = 1.0;
  x.v[1] = 2.0;

  JetT y(4.0);
  y.v[0] = 5.0;
  y.v[1] = 3.0;

  JetT r = hypot(x, y);
  (void)r;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
```