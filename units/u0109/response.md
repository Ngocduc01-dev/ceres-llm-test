**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm rẽ nhánh), nên chỉ có một đường đi duy nhất. Node 1 là câu lệnh `return Jet<T, N>(sin(f.a), cos(f.a) * f.v)`, trong đó `operator*` là phép nhân vô hướng với vector đạo hàm, không có rẽ nhánh.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f.a` là số thực bất kỳ (double); `f.v` là vector 7 phần tử double bất kỳ | `f.a` = 0.7, `f.v` = {0.3, -1.2, 2.5, 0.9, -0.4, 1.8, -2.1} (chọn cố định, không dùng sinh số ngẫu nhiên) |

**C. Nhánh không test**

Không có nhánh nào bị bỏ qua. Hàm không có điểm rẽ nhánh nên cũng không có `CHECK` và không có vòng lặp.

`C2 dự kiến = 0 / 0` (tổng số nhánh = 0, nên mọi nhánh đều đã được phủ; chỉ cần 1 test để chạy qua node 1).

**D. File test**

```cpp
// FILE: u0109_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetSinTest, TC1_P1_SinDouble7) {
  Jet<double, 7> f;
  f.a = 0.7;
  f.v[0] = 0.3;
  f.v[1] = -1.2;
  f.v[2] = 2.5;
  f.v[3] = 0.9;
  f.v[4] = -0.4;
  f.v[5] = 1.8;
  f.v[6] = -2.1;

  Jet<double, 7> r = sin(f);
  (void)r;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
```