**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào (hàm chỉ có 1 node tuần tự) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có tham số đầu vào. Tham số template `AmbientSpaceDimension` phải khác `Eigen::Dynamic` (nếu không `static_assert` ở dòng 124–126 báo lỗi khi biên dịch) | `AmbientSpaceDimension = 3` (khớp CFG `LineManifold<3>`) |

**C. Nhánh không test**

- Không có nhánh nào bị bỏ qua. `static_assert` được kiểm tra lúc biên dịch, không phải điểm rẽ nhánh lúc chạy và không có `CHECK`. CFG khớp với mã nguồn.
- Tổng số nhánh = 2 × 0 = 0, nên C2 không có mẫu số. Mọi node (node 1) đều được chạy.
- `C2 dự kiến = 0 / 0` (không có nhánh nào cần phủ, coi như đạt 100%, dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0168_test.cc
#include "gtest/gtest.h"
#include "ceres/line_manifold.h"

namespace ceres {

// TC1 - P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(LineManifoldConstructorTest, DefaultConstructorFixedSize3) {
  LineManifold<3> manifold;
  (void)manifold;
}

}  // namespace ceres
```