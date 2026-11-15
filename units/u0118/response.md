**A. Test paths**

Hàm không có điểm rẽ nhánh (0 điểm rẽ nhánh, 0 nhánh). Chỉ có một đường đi duy nhất, không có vòng lặp.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

Ghi chú: CFG chỉ có node 1 (dòng 693). Mã nguồn còn dòng 694 (`return Jet<T, N>(...)`) chạy liền sau node 1, nên thuộc cùng một đoạn lệnh. Điều này không ảnh hưởng đến đường đi.

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f.a` là số thực khác 0 (để đạo hàm hữu hạn), ví dụ trong [1, 10]; `f.v` là vector 2 phần tử, mỗi phần tử trong [-5, 5] | `f.a = 6.0`, `f.v = (2.0, -3.0)` |

**C. Nhánh không test**

Không có nhánh nào bị bỏ (không có điểm rẽ nhánh, không có `CHECK`).

`C2 dự kiến = 0 / 0` (không có nhánh nào; mọi câu lệnh đều chạy qua khi TC1 thực thi, tức C1 = 100%).

**D. File test**

```cpp
// FILE: u0118_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetCbrtTest, TC1_SinglePath) {
  Jet<double, 2> f;
  f.a = 6.0;
  f.v[0] = 2.0;
  f.v[1] = -3.0;

  Jet<double, 2> r = cbrt(f);
  (void)r;
}

}  // namespace
}  // namespace ceres
```