**CFG của unit** (không có điểm rẽ nhánh nào):

- START → node 1: `return (std::numeric_limits<difference_type>::max)() / sizeof(value_type);` → END

Số điểm rẽ nhánh = 0, tổng số nhánh = 0.

**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | n (kích thước mảng) từ 1 đến 5 | n = 3 (cố định, không dùng số ngẫu nhiên) |

**C. Nhánh không test:** không có. 

C2 dự kiến = 0 / 0 (hàm không có điểm rẽ nhánh; chỉ cần một test chạy qua node 1 là phủ toàn bộ hàm).

**D. File test**

```cpp
// FILE: u0029_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(FixedArrayMaxSize, P1_ReturnStatement) {
  ceres::internal::FixedArray<int, 5> arr(3, std::allocator<int>());
  arr.max_size();
}
```