**A. Test paths**

Hàm không có điểm rẽ nhánh nào (không `if`, vòng lặp, `switch`, `?:`, `CHECK`). CFG khớp với mã nguồn: node 1 gộp cả hai câu lệnh (dòng 157 và 158). Vì vậy chỉ có một đường đi.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `element`: con trỏ `double*` bất kỳ (không có điều kiện ràng buộc). Object `OrderedGroups<double*>` mới tạo, rỗng. | `element` = địa chỉ của biến cục bộ `double x = 3.0` |

**C. Nhánh không test**

Không có. Hàm có 0 điểm rẽ nhánh nên tổng số nhánh là 0. Không có vòng lặp và không có `CHECK`.

`C2 dự kiến = 0 / 0` (không có nhánh nào cần phủ, coi như 100%). Test P1 vẫn chạy qua toàn bộ node 1, nên phủ đủ câu lệnh. Đây là số dự kiến, chưa chạy thật.

**D. File test**

```cpp
// FILE: u0193_test.cc
#include "gtest/gtest.h"
#include "ceres/ordered_groups.h"

namespace ceres {
namespace internal {

// TC1 - P1: START -> 1 -> END (hàm không có điểm rẽ nhánh)
TEST(OrderedGroupsIsMemberTest, TC1_P1_NoBranch) {
  OrderedGroups<double*> obj;
  double x = 3.0;
  obj.IsMember(&x);
}

}  // namespace internal
}  // namespace ceres
```

Ghi chú: `OrderedGroups` nằm trong namespace `ceres`. Vì file đang ở trong `ceres::internal`, tên `OrderedGroups` vẫn được tìm thấy qua namespace bao ngoài `ceres`.