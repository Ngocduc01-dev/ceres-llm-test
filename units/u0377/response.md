**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm), nên chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh. Node 1 (`return e_cols_partition_`) luôn chạy. |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `elimination_groups[0]` từ 1 đến 1. Ma trận khối hợp lệ có 2 khối cột, mỗi khối cỡ từ 1 đến 2. Có 1 khối hàng cỡ 2. | `elimination_groups = {1}`. Hai khối cột cỡ 2 (vị trí 0 và 2). Một hàng có 2 cell: khối 0 (vị trí 0) và khối 1 (vị trí 4). Không dùng số ngẫu nhiên nên không cần seed. |

**C. Nhánh không test**

Không có nhánh nào bị bỏ. Hàm không có điểm rẽ nhánh nào và không có `CHECK` trong thân hàm.

Ghi chú: CFG khớp với mã nguồn. Tôi hiểu `PartitionedMatrixView<2>` là `kRowBlockSize = 2`, hai tham số còn lại lấy mặc định là `Eigen::Dynamic`. Các `CHECK` trong constructor của class vẫn thoả với dữ liệu đã chọn.

C2 dự kiến = 0 / 0 nhánh (không có điểm rẽ nhánh nên coi là 100%). Node 1 được phủ bởi TC1. Đây là giá trị dự kiến, chưa chạy thật.

**D. File test**

```cpp
// FILE: u0377_test.cc
#include "gtest/gtest.h"
#include "ceres/partitioned_matrix_view.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(PartitionedMatrixViewETest, ECColsPartitionP1) {
  // Cấu trúc khối: 1 khối hàng (cỡ 2), 2 khối cột (mỗi khối cỡ 2).
  auto* bs = new CompressedRowBlockStructure;

  bs->cols.emplace_back();
  bs->cols[0].size = 2;
  bs->cols[0].position = 0;
  bs->cols.emplace_back();
  bs->cols[1].size = 2;
  bs->cols[1].position = 2;

  bs->rows.emplace_back();
  CompressedRow& row = bs->rows[0];
  row.block.size = 2;
  row.block.position = 0;
  row.cells.emplace_back(0, 0);  // cell thuộc khối E (khối cột 0)
  row.cells.emplace_back(1, 4);  // cell thuộc khối F (khối cột 1)

  BlockSparseMatrix matrix(bs);

  LinearSolver::Options options;
  options.elimination_groups.push_back(1);

  PartitionedMatrixView<2> view(options, matrix);

  // Gọi unit một lần, không kiểm tra kết quả trả về.
  const std::vector<int>& partition = view.e_cols_partition();
  (void)partition;
}

}  // namespace internal
}  // namespace ceres
```