**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào (node 1: `return num_rows_`) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Số block từ 1 đến 5; kích thước mỗi block từ 1 đến 5; `context` = `nullptr`; `num_threads` = 1 | 2 block có kích thước 2 và 3 (vị trí 0 và 2), `context = nullptr`, `num_threads = 1` |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh, không có vòng lặp và không có `CHECK`. CFG khớp với mã nguồn.

`C2 dự kiến = 0 / 0 nhánh (không có nhánh nào; đường đi duy nhất P1 được phủ nên coi như 100%)`

**D. File test**

```cpp
// FILE: u0222_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_dense_matrix.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(BlockRandomAccessDenseMatrixNumRowsTest, P1_ReturnNumRows) {
  std::vector<Block> blocks;
  blocks.emplace_back(2, 0);
  blocks.emplace_back(3, 2);
  BlockRandomAccessDenseMatrix matrix(blocks, nullptr, 1);
  matrix.num_rows();
}

}  // namespace internal
}  // namespace ceres
```