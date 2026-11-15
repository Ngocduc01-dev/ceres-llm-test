**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm rẽ nhánh, tổng 0 nhánh). CFG chỉ có một node 1 nên chỉ có một test path.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f.a` là double bất kỳ, trong [-2, 2]; `f.v` là vector 2 phần tử, mỗi phần tử trong [-2, 2] | `f.a = 0.37`, `f.v = (-1.21, 0.84)` |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh, CFG khớp với mã nguồn.

`C2 dự kiến = 0 / 0` (không có nhánh nào; một test P1 phủ toàn bộ câu lệnh, tức đạt 100% C1 và C2 theo nghĩa hiển nhiên).

**D. File test**

```cpp
// FILE: u0115_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {

// TC1 - Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetTanhTest, SingleStraightLinePath) {
  Jet<double, 2> f;
  f.a = 0.37;
  f.v[0] = -1.21;
  f.v[1] = 0.84;

  Jet<double, 2> r = tanh(f);
  (void)r;  // Không kiểm tra kết quả trả về
}

}  // namespace ceres
```