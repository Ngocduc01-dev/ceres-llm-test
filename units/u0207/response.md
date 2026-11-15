**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `angle_axis[3]`: mỗi phần tử là số thực bất kỳ, chọn trong [-1, 1]. `R[9]`: mảng đầu ra, giá trị ban đầu tùy ý. | `angle_axis = {0.3, -0.7, 0.5}`, `R = {0, ..., 0}` (9 phần tử) |

**C. Nhánh không test**

- Không có nhánh nào, vì hàm có 0 điểm rẽ nhánh và không có `CHECK`.
- Hàm chỉ chuyển tiếp sang bản nạp chồng (overload) dùng `ColumnMajorAdapter3x3`. Các rẽ nhánh bên trong bản đó không thuộc CFG của unit này nên không tính.
- `C2 dự kiến = 0 / 0` (không có nhánh nào cần phủ, coi như 100%; chỉ cần đi qua node 1 một lần).

**D. File test**

```cpp
// FILE: u0207_test.cc
#include "gtest/gtest.h"
#include "ceres/rotation.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(AngleAxisToRotationMatrixTest, TC1_P1_ColumnMajorPointer) {
  const double angle_axis[3] = {0.3, -0.7, 0.5};
  double R[9] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  ceres::AngleAxisToRotationMatrix<double>(angle_axis, R);
}
```