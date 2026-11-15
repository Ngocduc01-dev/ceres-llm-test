**A. Test paths**

CFG khớp với mã nguồn. Unit không có điểm rẽ nhánh và không có vòng lặp, nên chỉ có 1 test path.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh (đi qua node 1) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Jet `a`: giá trị 1..10, k = 0 hoặc 1 (N = 2); `s` thuộc [1, 5] (khác 0 để tránh chia cho 0) | `a = Jet<double, 2>(4.0, 0)`, `s = 3.0` |

**C. Nhánh không test**

Không có nhánh nào bị bỏ qua, vì unit không có điểm rẽ nhánh.

`C2 dự kiến = 0 / 0` (không có nhánh nào; node 1 duy nhất được chạy qua bởi TC1).

**D. File test**

```cpp
// FILE: u0075_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetDivideAssignScalar, TC1_P1_Node1) {
  ceres::Jet<double, 2> a(4.0, 0);
  const double s = 3.0;
  a /= s;
}
```