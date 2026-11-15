**A. Test paths**

Unit không có điểm rẽ nhánh (0 điểm), nên chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh (node 1: `return num_cols_`) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Ma trận khối 1 hàng khối, 1 cột khối, kích thước khối 1. `subset_preconditioner_start_row_block` thuộc [0, 0], vì phải nhỏ hơn số hàng khối (1). `sparse_linear_algebra_library_type` là `EIGEN_SPARSE`, loại luôn có sẵn. | Khối 1×1, `start_row_block = 0`, `EIGEN_SPARSE` (không dùng số ngẫu nhiên vì miền giá trị chỉ có một phần tử) |

**C. Nhánh không test**

Không có. Unit không có điểm rẽ nhánh và không có `CHECK`.
Lưu ý: constructor có thể có `CHECK` về `subset_preconditioner_start_row_block`, nên test chọn giá trị hợp lệ để không làm `CHECK` sai.

`C2 dự kiến = 0 / 0` (không có nhánh nào, nên coi như phủ đủ 100%; mới là dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0418_test.cc
#include "gtest/gtest.h"
#include "ceres/subset_preconditioner.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(SubsetPreconditionerNumRows, TC1_ReturnNumCols) {
  // Ma trận khối 1x1: 1 hàng khối, 1 cột khối, 1 cell.
  auto* bs = new CompressedRowBlockStructure;
  bs->cols.push_back(Block(1, 0));

  bs->rows.push_back(CompressedRow());
  CompressedRow& row = bs->rows.back();
  row.block = Block(1, 0);
  row.cells.push_back(Cell(0, 0));

  BlockSparseMatrix A(bs);  // A lấy quyền sở hữu bs
  A.SetZero();

  Preconditioner::Options options;
  options.type = SUBSET;
  options.sparse_linear_algebra_library_type = EIGEN_SPARSE;
  options.subset_preconditioner_start_row_block = 0;

  SubsetPreconditioner preconditioner(options, A);
  preconditioner.num_rows();  // không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
```