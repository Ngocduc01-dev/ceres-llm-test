**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh (đường đi duy nhất) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f.a`, `g.a` ∈ [-10, 10] (double); `f.v`, `g.v` là vector 4 phần tử, mỗi phần tử ∈ [-10, 10]. Không có điều kiện ràng buộc. | f.a = 3.0, f.v = {1.0, -2.0, 4.0, 0.5}; g.a = -7.0, g.v = {2.0, 5.0, -3.0, 8.0} (giá trị cố định, tương đương chọn ngẫu nhiên với seed cố định) |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh và không có vòng lặp. Mã nguồn khớp với CFG (node 1 là câu lệnh `return` ở dòng 314).

C2 dự kiến = 0 / 0 (không có nhánh nào; mọi câu lệnh đều được phủ bởi TC1, tức 100%).

**D. File test**

```cpp
// FILE: u0078_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetOperatorPlusTest, AddTwoJets) {
  Jet<double, 4> f;
  f.a = 3.0;
  f.v[0] = 1.0;
  f.v[1] = -2.0;
  f.v[2] = 4.0;
  f.v[3] = 0.5;

  Jet<double, 4> g;
  g.a = -7.0;
  g.v[0] = 2.0;
  g.v[1] = 5.0;
  g.v[2] = -3.0;
  g.v[3] = 8.0;

  Jet<double, 4> h = operator+(f, g);
  (void)h;
}

}  // namespace ceres
```