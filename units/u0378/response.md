**A. Test paths**

Hàm có 0 điểm rẽ nhánh. CFG chỉ có START → 1 → END, nên chỉ có một path. Mã nguồn khớp với CFG.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh (node 1: `return f_cols_partition_`) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `elimination_groups[0]` = 1 (khối cột E) và ma trận 1 hàng khối, 2 khối cột kích thước 2. Đây là điều kiện để constructor không dừng vì `CHECK`. Hàm không có điều kiện rẽ nhánh nên không ràng buộc thêm. | `elimination_groups = {1}`, `cols = {Block(2,0), Block(2,2)}`, 1 hàng khối có `cells = {Cell(0,0), Cell(1,2)}`. Các giá trị cố định, không dùng số ngẫu nhiên nên không cần seed. |

**C. Nhánh không test**

- Không có nhánh nào cần bỏ qua, và cũng không có nhánh `CHECK` được tính vào tổng số nhánh.
- C2 dự kiến = 0 / 0. Hàm không có điểm rẽ nhánh, nên chỉ cần TC1 chạy node 1 là phủ trọn vẹn (xem là 100%, dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0378_test.cc
#include "gtest/gtest.h"
#include "ceres/partitioned_matrix_view.h"

namespace ceres {
namespace internal {

// TC1 - P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(PartitionedMatrixViewFColsPartition, ReturnsFColsPartition) {
  // Ma trận khối: 1 hàng khối (kích thước 2), 2 khối cột (mỗi khối kích thước 2).
  auto* bs = new CompressedRowBlockStructure;
  bs->cols.push_back(Block(2, 0));
  bs->cols.push_back(Block(2, 2));

  CompressedRow row;
  row.block = Block(2, 0);
  row.cells.push_back(Cell(0, 0));  // khối E
  row.cells.push_back(Cell(1, 2));  // khối F
  bs->rows.push_back(row);

  BlockSparseMatrix matrix(bs);  // matrix sở hữu bs

  LinearSolver::Options options;
  options.elimination_groups.push_back(1);  // 1 khối cột thuộc phần E

  PartitionedMatrixView<2, 2, 2> view(options, matrix);

  // Gọi unit một lần, không kiểm tra kết quả trả về.
  const std::vector<int>& f_cols = view.f_cols_partition();
  (void)f_cols;
}

}  // namespace internal
}  // namespace ceres
```