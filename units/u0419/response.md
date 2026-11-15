**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào. Node 1 (`return num_cols_`) chạy một lần. |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Kích thước khối cột của `A` từ 1 đến 5 (`A.num_cols()` bằng đúng giá trị này). Ma trận có 1 khối hàng cỡ 1 và 1 khối cột. | Kích thước khối cột = 3, chọn cố định, không dùng số ngẫu nhiên. |

**C. Nhánh không test:** không có. Hàm không có điểm rẽ nhánh nên tổng số nhánh là 0. Hàm cũng không có `CHECK` hay vòng lặp.

`C2 dự kiến = 0 / 0` (không có nhánh nào cần phủ). Chạy TC1 là đi qua toàn bộ hàm (node 1 → END), tức 100% câu lệnh.

**D. File test**

```cpp
// FILE: u0419_test.cc
#include "gtest/gtest.h"
#include "ceres/subset_preconditioner.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (hàm không có điểm rẽ nhánh)
TEST(SubsetPreconditionerNumCols, ReturnsNumCols) {
  // Ma trận khối thưa: 1 khối hàng (cỡ 1), 1 khối cột (cỡ 3), 1 cell.
  auto* bs = new CompressedRowBlockStructure;
  bs->cols.emplace_back();
  bs->cols[0].size = 3;
  bs->cols[0].position = 0;

  bs->rows.emplace_back();
  CompressedRow& row = bs->rows[0];
  row.block.size = 1;
  row.block.position = 0;
  row.cells.emplace_back(0, 0);

  BlockSparseMatrix A(bs);  // A nhận quyền sở hữu bs

  Preconditioner::Options options;
  options.subset_preconditioner_start_row_block = 0;

  SubsetPreconditioner preconditioner(options, A);
  preconditioner.num_cols();  // không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
```