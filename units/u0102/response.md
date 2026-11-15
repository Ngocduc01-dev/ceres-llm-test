**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm rẽ nhánh, 0 nhánh). CFG khớp với mã nguồn: chỉ có 1 node tuần tự. Không có vòng lặp và không có `CHECK`. Chỉ có 1 đường đi.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh nào (không có điểm rẽ nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f.a` trong (0, 10]; `f.v` là vector 2 phần tử, mỗi phần tử trong [-5, 5] | `f.a = 3.7`; `f.v = (1.3, -2.4)` |

**C. Nhánh không test**

Không có nhánh nào bị bỏ qua. Hàm không có điểm rẽ nhánh, nên tổng số nhánh là 0.

`C2 dự kiến = 0 / 0` (không có nhánh nào; toàn bộ hàm được phủ bởi 1 test chạy qua node 1, dự kiến 100%)

**D. File test**

```cpp
// FILE: u0102_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END (hàm không có điểm rẽ nhánh)
TEST(Log10JetTest, P1_SequentialPath) {
  ceres::Jet<double, 2> f;
  f.a = 3.7;
  f.v[0] = 1.3;
  f.v[1] = -2.4;

  ceres::Jet<double, 2> r = ceres::log10(f);
  (void)r;
}
```