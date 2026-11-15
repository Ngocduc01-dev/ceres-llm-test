**Ghi chú:** CFG khớp với mã nguồn (1 câu lệnh `return`, không có điểm rẽ nhánh, không có vòng lặp). Dùng `OrderedGroups<double *>` theo CFG.

**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh, không có nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có tham số đầu vào. Object `OrderedGroups<double *>` ở trạng thái mặc định (rỗng) | Object mặc định |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh và không có vòng lặp nên không cần test số lần lặp.

`C2 dự kiến = 0 / 0` (không có nhánh nào; một test đi hết đường START → 1 → END nên phủ toàn bộ câu lệnh, tức 100% theo quy ước).

**D. File test**

```cpp
// FILE: u0195_test.cc
#include "gtest/gtest.h"
#include "ceres/ordered_groups.h"

namespace ceres {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(OrderedGroupsNumGroupsTest, P1_DefaultObject) {
  OrderedGroups<double*> obj;
  obj.NumGroups();
}

}  // namespace ceres
```