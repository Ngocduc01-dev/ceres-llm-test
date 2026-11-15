**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Ma trận khối hợp lệ có 1 khối cột, 1 hàng khối, mỗi khối kích thước từ 1 đến 5. `use_page_locked_memory` là `false`. | Khối cột kích thước 2 tại vị trí 0. Hàng khối kích thước 2 tại vị trí 0, có 1 cell (`block_id` = 0, `position` = 0). `use_page_locked_memory` = false. |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh, nên không có nhánh nào cần test hay bị bỏ.

`C2 dự kiến = 0 / 0` (hàm không có nhánh, nên C2 coi là đạt đủ 100% khi P1 được chạy qua; dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0230_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END
TEST(BlockSparseMatrixNumRowsTest, P1_ReturnNumRows) {
  auto* block_structure = new CompressedRowBlockStructure;

  // 1 khối cột kích thước 2, bắt đầu tại vị trí 0.
  block_structure->cols.resize(1);
  block_structure->cols[0].size = 2;
  block_structure->cols[0].position = 0;

  // 1 hàng khối kích thước 2, có 1 cell trỏ tới khối cột 0.
  block_structure->rows.resize(1);
  block_structure->rows[0].block.size = 2;
  block_structure->rows[0].block.position = 0;
  block_structure->rows[0].cells.resize(1);
  block_structure->rows[0].cells[0].block_id = 0;
  block_structure->rows[0].cells[0].position = 0;

  // BlockSparseMatrix nhận quyền sở hữu block_structure.
  BlockSparseMatrix matrix(block_structure, false);

  matrix.num_rows();
}

}  // namespace internal
}  // namespace ceres
```