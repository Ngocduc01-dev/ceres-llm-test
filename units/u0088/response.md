**Ghi chú:** CFG không khớp mã nguồn (CFG nhắc đến `f.a`, `g_a_inverse`, còn mã nguồn là `s / g.a` và `minus_s_g_a_inverse2`). Theo yêu cầu, tôi tin mã nguồn. Cả hai đều không có điểm rẽ nhánh, hàm chỉ có 1 node thẳng.

**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `s` là double bất kỳ. `g.a` khác 0 (để tránh chia cho 0). `g.v` là vector 4 phần tử (N = 4). Không có điều kiện đường đi. | `s` = 3.5 (trong khoảng [1, 5]), `g.a` = 2.0 (trong khoảng [1, 5]), `g.v` = {1.0, 2.0, 3.0, 4.0}. Các giá trị cố định, không dùng số ngẫu nhiên. |

**C. Nhánh không test**

Không có nhánh nào (tổng số nhánh = 0, hàm không có điểm rẽ nhánh và không có `CHECK`).

`C2 dự kiến = 0 / 0` (không có nhánh nào, chỉ cần 1 test đi qua node 1 để phủ toàn bộ câu lệnh).

**D. File test**

```cpp
// FILE: u0088_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetOperatorDivScalarByJet, P1_StraightLine) {
  const double s = 3.5;
  Jet<double, 4> g;
  g.a = 2.0;
  g.v[0] = 1.0;
  g.v[1] = 2.0;
  g.v[2] = 3.0;
  g.v[3] = 4.0;

  Jet<double, 4> result = operator/(s, g);
  (void)result;
}

}  // namespace
}  // namespace ceres
```