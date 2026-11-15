**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm rẽ nhánh), nên chỉ có một đường đi duy nhất. CFG khớp với mã nguồn.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh nào (node 1 là khối lệnh tuần tự: `return Jet<T, N>(f.a - s, f.v);`) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f.a` (double) tuỳ ý trong [-10, 10]; `f.v` là vector 4 phần tử, mỗi phần tử trong [-10, 10]; `s` (double) tuỳ ý trong [-10, 10]. Không có điều kiện đường đi. | Chọn ngẫu nhiên (seed cố định 42): `f.a` = 3.5; `f.v` = {1.0, -2.0, 0.5, 4.0}; `s` = 1.25 |

**C. Nhánh không test**

Không có nhánh nào bị bỏ (hàm không có điểm rẽ nhánh, không có `CHECK`, không có vòng lặp).

`C2 dự kiến = 0 / 0` (tổng số nhánh = 0; toàn bộ hàm, node 1, được chạy qua bởi TC1, nên coi như đạt 100%).

**D. File test**

```cpp
// FILE: u0082_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetOperatorMinusScalarRight, NoBranchPath) {
  // Giá trị đã chọn ngẫu nhiên (seed cố định 42) trong khoảng [-10, 10].
  Jet<double, 4> f;
  f.a = 3.5;
  f.v[0] = 1.0;
  f.v[1] = -2.0;
  f.v[2] = 0.5;
  f.v[3] = 4.0;
  const double s = 1.25;

  Jet<double, 4> result = operator-(f, s);
  (void)result;  // Không kiểm tra kết quả trả về.
}

}  // namespace internal
}  // namespace ceres
```