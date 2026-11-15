**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Số khối cột: 1..2. Kích thước mỗi khối cột: 1..3. Số khối hàng: 1. `use_page_locked_memory = false`. `block_structure` khác `nullptr`, vì nếu là `nullptr` thì `CHECK` sai và chương trình dừng | 2 khối cột có kích thước 2 và 3 (vị trí 0 và 2). 1 khối hàng kích thước 1, có 2 cell. `use_page_locked_memory = false` |

**C. Nhánh không test**

- Không có nhánh nào cần loại. Hàm không có điểm rẽ nhánh, và `CHECK` trong constructor không thuộc unit nên không tính.
- `C2 dự kiến = 0 / 0` (không có nhánh nào, chỉ có một đường đi duy nhất START → 1 → END và TC1 đã phủ đường đó, coi như 100%; dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0231_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END
TEST(BlockSparseMatrixNumColsTest, P1_ReturnNumCols) {
  auto* block_structure = new CompressedRowBlockStructure;

  // Hai khối cột: kích thước 2 (vị trí 0) và 3 (vị trí 2).
  block_structure->cols.push_back(Block(2, 0));
  block_structure->cols.push_back(Block(3, 2));

  // Một khối hàng kích thước 1, có 2 cell trỏ tới 2 khối cột.
  block_structure->rows.emplace_back();
  CompressedRow& row = block_structure->rows.back();
  row.block = Block(1, 0);
  row.cells.push_back(Cell(0, 0));
  row.cells.push_back(Cell(1, 2));

  // Matrix nhận quyền sở hữu block_structure.
  BlockSparseMatrix matrix(block_structure, false);

  matrix.num_cols();
}

}  // namespace internal
}  // namespace ceres
```