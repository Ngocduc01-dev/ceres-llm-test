**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có điểm rẽ nhánh nào (hàm chỉ có một đường đi duy nhất) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Kích thước mảng n: 1 đến 5 (không có điều kiện ràng buộc; chọn n ≤ 5 theo yêu cầu dữ liệu nhỏ). Giá trị phần tử: 0 đến 100 | n = 3 (`FixedArray<int, 20>` có 3 phần tử, giá trị khởi tạo 7) |

**C. Nhánh không test:** Không có. Hàm không có điểm rẽ nhánh và không có vòng lặp, `CHECK` cũng không có. CFG khớp với mã nguồn.
`C2 dự kiến = 0 / 0` (không có nhánh nào; hàm chỉ có một đường đi START → END nên được phủ hoàn toàn khi gọi 1 lần, coi như 100%).

**D. File test**

```cpp
// FILE: u0044_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// Path P1: START -> END (không có điểm rẽ nhánh)
TEST(FixedArrayRend, TC1_P1_ConstRend) {
  const ceres::internal::FixedArray<int, 20> arr(3, 7);
  const auto it = arr.rend();
  (void)it;
}
```