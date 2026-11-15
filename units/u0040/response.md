**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Kích thước mảng n: 1 đến 5 (`FixedArray<int, 20>` dùng bộ nhớ inline vì n ≤ 20) | n = 3 (giá trị phần tử 0 theo constructor `FixedArray(size_type n, const allocator_type&)`) |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh, nên không có nhánh nào bị bỏ. Tổng số nhánh = 0, chỉ cần một đường đi START → END.

C2 dự kiến = 0 / 0 (không có nhánh; đường đi duy nhất P1 được chạy qua, tương đương 100%)

**D. File test**

```cpp
// FILE: u0040_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// P1: START -> END (không có điểm rẽ nhánh)
TEST(FixedArrayRbeginTest, TC1_NoBranch) {
  ceres::internal::FixedArray<int, 20> arr(3, std::allocator<int>());
  auto it = arr.rbegin();
  (void)it;  // không kiểm tra kết quả trả về
}
```