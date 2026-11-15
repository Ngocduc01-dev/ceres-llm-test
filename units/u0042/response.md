**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có điểm rẽ nhánh nào (hàm chỉ gọi `rbegin()` rồi trả về) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Số phần tử `n` của `FixedArray<int, 20>`: 1 đến 5; giá trị phần tử: 0 đến 9 | `n` = 3; giá trị fill = 7 (chọn cố định, không dùng số ngẫu nhiên) |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh nào, nên tổng số nhánh là 0 và không có nhánh nào bị bỏ. Không có `CHECK` trong hàm.
`C2 dự kiến = 0 / 0` (không có nhánh nào; mọi câu lệnh của hàm đều được chạy bởi TC1, tức đạt 100% theo quy ước).

CFG khớp với mã nguồn.

**D. File test**

```cpp
// FILE: u0042_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// Path P1: START -> END (không có điểm rẽ nhánh)
TEST(FixedArrayCrbeginTest, P1_NoBranch) {
  const ceres::internal::FixedArray<int, 20> arr(3, 7);
  auto it = arr.crbegin();
  (void)it;
}
```