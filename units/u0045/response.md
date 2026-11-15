**A. Test paths**

Hàm `crend()` không có điểm rẽ nhánh (CFG chỉ có START → END), nên chỉ có một đường đi.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Kích thước mảng n từ 1 đến 5 (không ảnh hưởng đường đi) | n = 3 (chọn cố định), giá trị phần tử = 7 |

**C. Nhánh không test**

Không có nhánh nào bị bỏ qua (hàm không có điểm rẽ nhánh, không có `CHECK`).
`C2 dự kiến = 0 / 0` (tổng số nhánh = 0, nên mọi đường đi qua hàm đều thỏa C2; TC1 gọi hàm một lần và đi qua toàn bộ START → END).

**D. File test**

```cpp
// FILE: u0045_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// P1: START -> END (không có điểm rẽ nhánh)
TEST(FixedArrayCrendTest, P1_NoBranch) {
  ceres::internal::FixedArray<int, 20> arr(3, 7);
  auto it = arr.crend();
  (void)it;
}
```