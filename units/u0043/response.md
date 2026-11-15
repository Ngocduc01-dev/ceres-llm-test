**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có điểm rẽ nhánh (0 điểm, 0 nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `FixedArray<int, 20>` với n từ 1 đến 5 (n ≤ 20 nên dùng bộ nhớ inline); giá trị phần tử từ 0 đến 100 | n = 3, các phần tử = {17, 42, 85} (chọn cố định, không dùng số ngẫu nhiên) |

**C. Nhánh không test:** Không có. Hàm không có điểm rẽ nhánh nên không có nhánh nào cần phủ và không có vòng lặp.
`C2 dự kiến = 0 / 0` (không có nhánh; hàm được phủ hoàn toàn bởi 1 test đi qua START → END, tức 100% theo quy ước).

**D. File test:**

```cpp
// FILE: u0043_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// Path P1: START -> END (không có điểm rẽ nhánh)
TEST(FixedArrayRend, P1_NoBranch) {
  ceres::internal::FixedArray<int, 20> arr({17, 42, 85});
  auto it = arr.rend();
  (void)it;
}
```