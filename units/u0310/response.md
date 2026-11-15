**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh (0 nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có tham số đầu vào; object `WeightedGraph<int>` được tạo bằng constructor mặc định (đồ thị rỗng) | Không có (đồ thị rỗng) |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh nào và không có vòng lặp. CFG khớp với mã nguồn.

C2 dự kiến = 0 / 0 (không có nhánh nào; mọi câu lệnh đều được chạy qua bởi TC1, tức phủ 100%)

**D. File test**

```cpp
// FILE: u0310_test.cc
#include "gtest/gtest.h"
#include "ceres/graph.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(WeightedGraphVerticesTest, P1_ReturnVerticesOfDefaultGraph) {
  ceres::internal::WeightedGraph<int> graph;
  const auto& vertices = graph.vertices();
  (void)vertices;
}
```