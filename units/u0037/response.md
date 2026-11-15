**Điểm rẽ nhánh:** 0 → tổng số nhánh = 0. Hàm chỉ có node 1 (`return data()`), chỉ có một đường đi duy nhất. Mã nguồn khớp với CFG.

**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | n (kích thước mảng) từ 1 đến 5; giá trị phần tử bất kỳ | n = 3 (chọn cố định, seed không cần); phần tử 1.5 |

**C. Nhánh không test**

Không có. Không có nhánh nào bị bỏ qua (`CHECK` không xuất hiện trong hàm).

`C2 dự kiến = 0 / 0` (hàm không có điểm rẽ nhánh; node 1 được phủ bởi TC1, nên coi như đạt 100%).

**D. File test**

```cpp
// FILE: u0037_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

#include <memory>

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(FixedArrayBeginConst, P1_ReturnData) {
  using Array = ceres::internal::FixedArray<double>;
  const Array array(3, 1.5, std::allocator<double>());
  Array::const_iterator it = array.begin();
  (void)it;
}
```