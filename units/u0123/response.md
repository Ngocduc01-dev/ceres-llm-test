**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm rẽ nhánh), nên CFG chỉ có một đường đi duy nhất. Node 1 là lệnh `return`, trong đó có gọi `fma` kiểu `double` và các phép `operator*`.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh nào (hàm không có điểm rẽ nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có điều kiện đường đi, nên mọi giá trị đều hợp lệ. Với `Jet<double, 2>`, mỗi `x`, `y`, `z` có phần giá trị `a` và vector đạo hàm `v` gồm 2 phần tử. Chọn `a` trong [-5, 5] và `v[i]` trong [-5, 5]. | x: a = 1.5, v = {0.5, -2.0}; y: a = -3.0, v = {1.0, 4.0}; z: a = 2.5, v = {-1.5, 3.0} (giá trị cố định, chọn trong khoảng trên) |

**C. Nhánh không test**

Không có nhánh nào cần bỏ qua, vì hàm không có điểm rẽ nhánh. Tổng số nhánh là 0, nên C2 đạt tối đa chỉ với 1 test đi qua node 1.

`C2 dự kiến = 0 / 0 (không có điểm rẽ nhánh; 1 test đi qua toàn bộ đường START → 1 → END, tức phủ 100% câu lệnh)`

**D. File test**

```cpp
// FILE: u0123_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetFmaTest, TC1_SingleStraightPath) {
  using JetT = Jet<double, 2>;

  JetT x(1.5);
  x.v[0] = 0.5;
  x.v[1] = -2.0;

  JetT y(-3.0);
  y.v[0] = 1.0;
  y.v[1] = 4.0;

  JetT z(2.5);
  z.v[0] = -1.5;
  z.v[1] = 3.0;

  JetT r = fma(x, y, z);
  (void)r;  // không kiểm tra kết quả trả về
}

}  // namespace
}  // namespace ceres
```