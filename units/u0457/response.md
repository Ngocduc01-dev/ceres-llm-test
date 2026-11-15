**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → END | node 2: đúng |
| P2 | START → 1 → 2 → 4 → END | node 2: sai |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Object rỗng (chưa có phần tử nào), nên `find` trả về `end()`. `element` là con trỏ `double*` bất kỳ. | Object rỗng, `element = &x[0]` |
| TC2 | P2 | `element` đã được thêm vào object bằng `AddElementToGroup`, nên `find` tìm thấy. Group id nằm trong [0, 5]. | `element = &x[1]`, group id = 3 |

**C. Nhánh không test:** không có. Cả 2 nhánh của node 2 đều có test.

Lưu ý: CFG khớp với mã nguồn. Hàm không có vòng lặp và không có `CHECK`.

`C2 dự kiến = 2 / 2` (dự kiến, chưa chạy thật)

**D. File test**

```cpp
// FILE: u0457_test.cc
#include "gtest/gtest.h"
#include "ceres/ordered_groups.h"

namespace ceres {

// P1: START -> 1 -> 2 -> 3 -> END (node 2: đúng)
TEST(OrderedGroupsGroupIdTest, ElementNotFound) {
  OrderedGroups<double*> groups;
  double x[2] = {1.0, 2.0};
  groups.GroupId(&x[0]);
}

// P2: START -> 1 -> 2 -> 4 -> END (node 2: sai)
TEST(OrderedGroupsGroupIdTest, ElementFound) {
  OrderedGroups<double*> groups;
  double x[2] = {1.0, 2.0};
  groups.AddElementToGroup(&x[1], 3);
  groups.GroupId(&x[1]);
}

}  // namespace ceres
```