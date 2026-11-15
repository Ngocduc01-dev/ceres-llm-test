**A. Test paths**

Điểm rẽ nhánh duy nhất là node 2 (toán tử `?:`), nên tổng số nhánh là 2. Node 1 (`find`) và node 4 (`operator->`) không phải điểm rẽ nhánh. CFG khớp với mã nguồn. Hàm không có vòng lặp.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → END | node 2: đúng (`it == end()`, không tìm thấy group) |
| P2 | START → 1 → 2 → 4 → 3 → END | node 2: sai (`it != end()`, tìm thấy group) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Object rỗng (chưa thêm phần tử nào); `group` trong [0, 5] | `group` = 3 |
| TC2 | P2 | Đã gọi `AddElementToGroup(&x, g)` với g trong [0, 5]; gọi `GroupSize(g)` với đúng g đó | g = 2 |

**C. Nhánh không test**

Không có nhánh nào bị bỏ. Không có `CHECK` và không có nhánh không thể đi tới.

`C2 dự kiến = 2 / 2`

**D. File test**

```cpp
// FILE: u0458_test.cc
#include "gtest/gtest.h"
#include "ceres/ordered_groups.h"

// P1: START -> 1 -> 2 -> 3 -> END (node 2: đúng)
TEST(OrderedGroupsGroupSize, GroupNotFound) {
  ceres::OrderedGroups<double*> obj;
  const int group = 3;
  obj.GroupSize(group);
}

// P2: START -> 1 -> 2 -> 4 -> 3 -> END (node 2: sai)
TEST(OrderedGroupsGroupSize, GroupFound) {
  ceres::OrderedGroups<double*> obj;
  double x = 1.0;
  const int group = 2;
  obj.AddElementToGroup(&x, group);
  obj.GroupSize(group);
}
```