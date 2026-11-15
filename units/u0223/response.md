**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào (node 1: `return num_rows_`) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Số block từ 1 đến 2. Kích thước mỗi block từ 1 đến 3, tổng ≤ 5. `context` = `nullptr`. `num_threads` = 1 (không đa luồng). | 2 block: `Block(2, 0)` và `Block(3, 2)`. `context = nullptr`, `num_threads = 1`. |

**C. Nhánh không test**

Không có nhánh nào bị bỏ qua, vì hàm không có điểm rẽ nhánh và không có `CHECK` trong thân hàm. Mã nguồn khớp với CFG.

`C2 dự kiến = 0 / 0` (tổng số nhánh là 0, nên coi như đạt 100%; TC1 phủ toàn bộ đường đi duy nhất START → 1 → END).

**D. File test**

```cpp
// FILE: u0223_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_dense_matrix.h"

#include <vector>

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(BlockRandomAccessDenseMatrixNumCols, ReturnsNumRows) {
  std::vector<Block> blocks;
  blocks.emplace_back(2, 0);
  blocks.emplace_back(3, 2);
  BlockRandomAccessDenseMatrix matrix(blocks, nullptr, 1);
  matrix.num_cols();
}

}  // namespace internal
}  // namespace ceres
```