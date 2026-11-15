**A. Test paths**

Hàm không có điểm rẽ nhánh (0 điểm rẽ nhánh), nên chỉ có 1 test path. CFG khớp với mã nguồn (node 1 là biểu thức `Jet<T, N>(cosh(f.a), sinh(f.a) * f.v)`, trong đó có `operator*`).

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh nào (không có điểm rẽ nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f.a`: bất kỳ số thực double (không có điều kiện ràng buộc), chọn trong [-2, 2]; `f.v`: vector 2 phần tử double, mỗi phần tử trong [-2, 2] | `f.a = 0.7`, `f.v = (-1.3, 0.4)` (giá trị cố định, không dùng sinh số ngẫu nhiên) |

**C. Nhánh không test**

Không có. Hàm không có vòng lặp và không có `CHECK`.

`C2 dự kiến = 0 / 0` (không có nhánh nào; hàm có 1 đường đi duy nhất nên được phủ hoàn toàn bởi TC1).

**D. File test**

```cpp
// FILE: u0114_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetCoshTest, TC1_SingleStraightPath) {
  Jet<double, 2> f;
  f.a = 0.7;
  f.v[0] = -1.3;
  f.v[1] = 0.4;

  Jet<double, 2> r = cosh(f);
  (void)r;  // Không kiểm tra kết quả trả về
}

}  // namespace
}  // namespace ceres
```