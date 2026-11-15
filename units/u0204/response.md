**A. Test paths**

Hàm có 0 điểm rẽ nhánh, nên chỉ có 1 test path. CFG khớp với mã nguồn (`pointer_[r * row_stride + c * col_stride]`, với `row_stride = 1`, `col_stride = 3`).

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Mảng 5 phần tử `double`. `r` thuộc [0, 1] và `c` thuộc [0, 1], để chỉ số `r*1 + c*3` thuộc [0, 4] và nằm trong mảng. | `data = {1.5, 2.5, 3.5, 4.5, 5.5}`, `r = 1`, `c = 1` (chỉ số 4) |

**C. Nhánh không test**

Không có nhánh nào bị bỏ qua, vì hàm không có điểm rẽ nhánh và cũng không có `CHECK`.

`C2 dự kiến = 0 / 0` (không có nhánh nào cần phủ; path P1 phủ toàn bộ hàm, tức coi như 100%, dự kiến chưa chạy thật).

**D. File test**

```cpp
// FILE: u0204_test.cc
#include "gtest/gtest.h"
#include "ceres/rotation.h"

// Path P1: START -> 1 -> END (hàm không có điểm rẽ nhánh)
TEST(MatrixAdapterOperatorCall, P1_SingleStatement) {
  const double data[5] = {1.5, 2.5, 3.5, 4.5, 5.5};
  ceres::MatrixAdapter<const double, 1, 3> m(data);
  const double& value = m(1, 1);
  (void)value;
}
```