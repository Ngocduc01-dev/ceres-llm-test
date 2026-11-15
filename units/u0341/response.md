**A. Test paths**

Hàm không có điểm rẽ nhánh nào (tổng số nhánh = 0). CFG khớp với mã nguồn. Chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh (node 1: `return tangent_size_`) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `size` từ 1 đến 5; `constant_parameters` là tập con có phần tử khác nhau trong [0, size−1], tối đa `size − 1` phần tử (để CHECK trong constructor không dừng chương trình) | `size = 4`, `constant_parameters = {1, 3}` |

**C. Nhánh không test**

Không có nhánh nào bị bỏ (hàm không có điểm rẽ nhánh, không có vòng lặp, không có `CHECK`).

C2 dự kiến = 0 / 0 (không có nhánh nào; node 1 được chạy qua nên đạt phủ câu lệnh 100%).

**D. File test**

```cpp
// FILE: u0341_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

#include <vector>

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(SubsetManifoldTangentSize, P1_ReturnTangentSize) {
  const int size = 4;
  const std::vector<int> constant_parameters = {1, 3};
  ceres::SubsetManifold manifold(size, constant_parameters);
  manifold.TangentSize();
}
```