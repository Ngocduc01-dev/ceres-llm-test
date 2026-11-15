**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm rẽ nhánh, 0 nhánh). Chỉ có một đường đi duy nhất. Biểu thức `==` chỉ trả về giá trị `true` hoặc `false`, không tạo nhánh điều khiển.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f.a`, `g.a` là double bất kỳ (không có điều kiện đường đi); dùng `Jet<double, 2>` | `f = Jet(3.0, 0)`, `g = Jet(5.0, 1)` (cố định, giả lập ngẫu nhiên với seed cố định) |

**C. Nhánh không test**

Không có nhánh nào bị bỏ (tổng số nhánh = 0).
`C2 dự kiến = 0 / 0` (không có điểm rẽ nhánh nên C2 coi như đạt đầy đủ khi node 1 được chạy qua; dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0094_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetOperatorEqualTest, P1_SinglePath) {
  using JetT = Jet<double, 2>;
  JetT f(3.0, 0);
  JetT g(5.0, 1);
  bool result = (f == g);
  (void)result;  // Không kiểm tra kết quả trả về
}

}  // namespace
}  // namespace ceres
```