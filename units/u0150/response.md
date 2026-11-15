**A. Test paths**

Hàm không có điểm rẽ nhánh (CFG ghi 0). Mã nguồn khớp CFG: node 1 gồm dòng 1161 và lệnh `return` ở dòng 1162, cả hai chạy liền nhau. Vì vậy chỉ có một đường đi.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh nào (không có điểm rẽ nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f.a` ∈ [0.5, 5] (không có điều kiện đường đi nên chọn giá trị dương cho phép toán `pow` xác định). `g` ∈ [-3, 3]. `f.v` gồm 2 phần tử, mỗi phần tử ∈ [-2, 2] | `f.a` = 2.7, `g` = 1.8, `f.v` = (1.0, 0.5) |

**C. Nhánh không test**

Không có nhánh nào, vì tổng số nhánh là 0 (không có `CHECK` hay điểm rẽ nhánh).

`C2 dự kiến = 0 / 0` (không có nhánh để phủ; mọi câu lệnh đều chạy qua trong TC1; dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0150_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có nhánh)
TEST(JetPowDoubleExponent, P1_StraightLine) {
  Jet<double, 2> f(2.7, 0);  // a = 2.7, v = (1, 0)
  f.v[0] = 1.0;
  f.v[1] = 0.5;
  const double g = 1.8;

  Jet<double, 2> r = pow(f, g);
  (void)r;  // không kiểm tra kết quả
}

}  // namespace internal
}  // namespace ceres
```