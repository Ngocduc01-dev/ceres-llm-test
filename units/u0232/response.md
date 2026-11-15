**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Cấu trúc khối hợp lệ (khác `nullptr`): 1 khối cột, 1 hàng khối, 1 cell. Kích thước khối từ 1 đến 5. | Khối cột kích thước 2, hàng khối kích thước 2, 1 cell tại vị trí 0. `use_page_locked_memory = false`. |

**C. Nhánh không test**

- Không có nhánh nào bị bỏ qua. Unit chỉ có 1 lệnh `return`, không có vòng lặp.
- `CHECK` nằm trong constructor, không nằm trong unit. Test không làm `CHECK` sai, vì `block_structure` được truyền vào là hợp lệ.
- CFG khớp với mã nguồn.
- `C2 dự kiến = 0 / 0` (unit không có điểm rẽ nhánh, nên chỉ cần gọi hàm một lần là đi hết đường duy nhất, tức phủ đầy đủ).

**D. File test**

```cpp
// FILE: u0232_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(BlockSparseMatrixNumNonzerosTest, TC1_P1_ReturnNumNonzeros) {
  auto* block_structure = new CompressedRowBlockStructure;

  // Một khối cột kích thước 2, bắt đầu tại vị trí 0.
  block_structure->cols.push_back(Block(2, 0));

  // Một hàng khối kích thước 2, chứa một cell trỏ tới khối cột 0.
  CompressedRow row;
  row.block = Block(2, 0);
  row.cells.push_back(Cell(0, 0));
  block_structure->rows.push_back(row);

  // Constructor nhận quyền sở hữu block_structure.
  BlockSparseMatrix matrix(block_structure, false);

  // Không kiểm tra kết quả trả về, chỉ gọi hàm.
  matrix.num_nonzeros();
}

}  // namespace internal
}  // namespace ceres
```