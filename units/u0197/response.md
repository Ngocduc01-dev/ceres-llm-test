**A. Test paths**

CFG: `START → node 1 (return element_to_group_;) → END`. Hàm không có điểm rẽ nhánh nào, nên tổng số nhánh là 0.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh nào (đường đi duy nhất) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có tham số. Object `OrderedGroups<int>` mặc định, T = `int` | Không áp dụng (không có đầu vào ngẫu nhiên, không cần seed) |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh và không có vòng lặp.
`C2 dự kiến = 0 / 0` (không có nhánh nào, xem như đạt 100%; path P1 phủ toàn bộ câu lệnh).

**D. File test**

```cpp
// FILE: u0197_test.cc
#include "gtest/gtest.h"
#include "ceres/ordered_groups.h"

namespace ceres {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(OrderedGroupsElementToGroupTest, DefaultObjectReturnsMapReference) {
  OrderedGroups<int> obj;
  const std::map<int, int>& result = obj.element_to_group();
  static_cast<void>(result);  // Không kiểm tra kết quả trả về
}

}  // namespace ceres
```