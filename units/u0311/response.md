**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm rẽ nhánh, 0 nhánh, không có vòng lặp, không có `CHECK`). Chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh rẽ nào (đường thẳng) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có tham số đầu vào. Hàm là `static`, không phụ thuộc trạng thái object. Kiểu template: `WeightedGraph<int>` (theo CFG) | Không có; dùng `WeightedGraph<int> obj;` rồi gọi `obj.InvalidWeight()` |

**C. Nhánh không test**

Không có nhánh nào bị bỏ qua (hàm không có điểm rẽ nhánh, không có `CHECK`).
`C2 dự kiến = 0 / 0` (không có nhánh nào; mọi câu lệnh, gồm node 1, đều được chạy qua bởi TC1, tức phủ 100% theo quy ước).

**D. File test**

```cpp
// FILE: u0311_test.cc
#include "gtest/gtest.h"
#include "ceres/graph.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(WeightedGraphInvalidWeightTest, TC1_StraightPath) {
  WeightedGraph<int> obj;
  obj.InvalidWeight();
}

}  // namespace internal
}  // namespace ceres
```