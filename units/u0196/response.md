**A. Test paths**

Hàm không có điểm rẽ nhánh nào (tổng số nhánh = 0). CFG khớp với mã nguồn, chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có tham số đầu vào. Object `OrderedGroups<double*>` tạo bằng constructor mặc định, không ràng buộc nào | Object mặc định (rỗng) |

**C. Nhánh không test**

Không có nhánh nào (không có điểm rẽ nhánh, không có `CHECK`).
`C2 dự kiến = 0 / 0` (không có nhánh nào cần phủ; đường đi duy nhất P1 được chạy qua, độ phủ coi như 100%).

**D. File test**

```cpp
// FILE: u0196_test.cc
#include "gtest/gtest.h"
#include "ceres/ordered_groups.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(OrderedGroupsGroupToElements, P1_ReturnsGroupToElements) {
  ceres::OrderedGroups<double*> obj;
  const auto& result = obj.group_to_elements();
  (void)result;
}
```