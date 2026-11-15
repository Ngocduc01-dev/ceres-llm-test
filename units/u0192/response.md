**A. Test paths**

Hàm `Clear()` có 0 điểm rẽ nhánh, nên chỉ có một đường đi duy nhất. CFG khớp với mã nguồn.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Object `OrderedGroups<double*>` đã thêm 0 đến 5 phần tử. Nhóm của mỗi phần tử là số nguyên từ 0 đến 5. | Hai phần tử: `a` vào nhóm 3, `b` vào nhóm 1. Sau đó gọi `Clear()` một lần. |

**C. Nhánh không test**

- Không có nhánh nào bị bỏ qua. Hàm không có vòng lặp và không có `CHECK`.
- C2 dự kiến = 0 / 0 (tổng số nhánh bằng 0, nên mọi nhánh đều được phủ). Chỉ cần node 1 chạy qua là đạt C1 và C2.

**D. File test**

```cpp
// FILE: u0192_test.cc
#include "gtest/gtest.h"
#include "ceres/ordered_groups.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(OrderedGroupsClear, P1_ClearNonEmptyGroups) {
  ceres::OrderedGroups<double*> obj;
  double a = 1.0;
  double b = 2.0;
  obj.AddElementToGroup(&a, 3);
  obj.AddElementToGroup(&b, 1);
  obj.Clear();
}
```