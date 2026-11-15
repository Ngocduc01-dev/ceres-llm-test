**A. Test paths**

Hàm `vertices() const` có 0 điểm rẽ nhánh, nên chỉ có một đường đi duy nhất. CFG khớp với mã nguồn.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh. Node 1: `return vertices_` |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Graph<int> mặc định, không có đầu vào nào khác (không ràng buộc) | `Graph<int> graph;` (đồ thị rỗng) |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh và không có vòng lặp hay `CHECK`.

C2 dự kiến = 0 / 0 (không có nhánh nào; đường đi duy nhất P1 được chạy qua, tức phủ 100% theo quy ước).

**D. File test**

```cpp
// FILE: u0309_test.cc
#include "gtest/gtest.h"
#include "ceres/graph.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(GraphVerticesTest, P1_ReturnVertices) {
  Graph<int> graph;
  const auto& vertices = graph.vertices();
  (void)vertices;
}

}  // namespace internal
}  // namespace ceres
```