**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có tham số đầu vào. Object `OrderedGroups<double *>` được tạo bằng constructor mặc định, không có phần tử nào. | Không có giá trị nào để chọn. Không dùng số ngẫu nhiên. |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh, không có vòng lặp và không có `CHECK`. CFG khớp với mã nguồn.

C2 dự kiến = 0 / 0 (hàm không có nhánh nên coi là phủ 100%). Một test đi qua START → 1 → END là đủ.

**D. File test**

```cpp
// FILE: u0194_test.cc
#include "gtest/gtest.h"
#include "ceres/ordered_groups.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(OrderedGroupsNumElements, P1_StraightLine) {
  ceres::OrderedGroups<double*> obj;
  obj.NumElements();
}
```