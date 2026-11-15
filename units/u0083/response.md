**A. Test paths**

Hàm không có điểm rẽ nhánh (0 điểm rẽ nhánh, tổng số nhánh = 0). CFG khớp với mã nguồn. Chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `s`: số double bất kỳ; `f.a`: double bất kỳ; `f.v`: vector 4 phần tử double bất kỳ (không có điều kiện ràng buộc) | `s = 3.5`; `f.a = 1.25`; `f.v = {0.5, -1.5, 2.0, 4.0}` (chọn cố định, trong khoảng [-5, 5]) |

**C. Nhánh không test**

Không có nhánh nào bị bỏ qua (hàm không có điểm rẽ nhánh, không có `CHECK`).

`C2 dự kiến = 0 / 0` (không có nhánh nào; mọi node, gồm node 1, đều được chạy qua bởi TC1, tức phủ câu lệnh 100%).

**D. File test**

```cpp
// FILE: u0083_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetOperatorMinusScalarJet, ScalarMinusJet) {
  using JetT = Jet<double, 4>;

  const double s = 3.5;
  JetT f;
  f.a = 1.25;
  f.v[0] = 0.5;
  f.v[1] = -1.5;
  f.v[2] = 2.0;
  f.v[3] = 4.0;

  // Gọi unit đúng một lần; không kiểm tra kết quả trả về.
  JetT r = operator-(s, f);
  (void)r;
}

}  // namespace
}  // namespace ceres
```