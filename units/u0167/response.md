**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có tham số đầu vào. Object là `LineManifold<3>` tạo bằng constructor mặc định, không cần chọn giá trị ngẫu nhiên. | `LineManifold<3>` (`size_` = 3) |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh và không có `CHECK`. Một test đi qua P1 là phủ toàn bộ hàm.

`C2 dự kiến = 0 / 0` (không có nhánh nào, đạt 100% theo quy ước). Toàn bộ câu lệnh ở node 1 đều được chạy.

**D. File test**

```cpp
// FILE: u0167_test.cc
#include "gtest/gtest.h"
#include "ceres/line_manifold.h"

// P1: START -> 1 -> END (hàm không có điểm rẽ nhánh)
TEST(LineManifoldTangentSizeTest, P1_StraightLineNoBranch) {
  ceres::LineManifold<3> manifold;
  int tangent_size = manifold.TangentSize();
  (void)tangent_size;  // Không kiểm tra kết quả trả về.
}
```