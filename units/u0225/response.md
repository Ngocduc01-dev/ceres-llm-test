**A. Test paths**

Unit `mutable_values()` không có điểm rẽ nhánh và không có vòng lặp. Chỉ có một đường đi.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh (0 điểm rẽ nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Số block: 1–3. Kích thước mỗi block: 1–5. `context`: `nullptr`. `num_threads`: 1 | 2 block, kích thước 2 và 3 (`Block(2, 0)`, `Block(3, 2)`), `context = nullptr`, `num_threads = 1` |

**C. Nhánh không test**

Không có. Unit không có điểm rẽ nhánh và không có `CHECK`.

`C2 dự kiến = 0 / 0` (không có nhánh nào cần phủ, node 1 được chạy qua nên đạt 100%; dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0225_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_dense_matrix.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END
TEST(BlockRandomAccessDenseMatrixMutableValuesTest, P1_ReturnValuesPointer) {
  std::vector<Block> blocks;
  blocks.emplace_back(2, 0);
  blocks.emplace_back(3, 2);
  BlockRandomAccessDenseMatrix matrix(blocks, nullptr, 1);
  double* values = matrix.mutable_values();
  (void)values;
}

}  // namespace internal
}  // namespace ceres
```

Ghi chú: giả định `Block` có constructor `Block(int size, int position)` như trong Ceres 2.2.0. `Block` được lấy qua header của `BlockRandomAccessDenseMatrix`, không cần thêm `#include`.