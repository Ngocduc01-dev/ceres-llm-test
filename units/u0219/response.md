**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Ma trận `A` là `BlockSparseMatrix` có 1 row block và 1 col block, kích thước mỗi block từ 1 đến 2. Có 1 cell. `options` để mặc định. | Kích thước block = 1 (chọn cố định, không dùng số ngẫu nhiên). |

**C. Nhánh không test**

Không có. Unit là destructor `= default`, nên CFG chỉ có `START → END` và không có điểm rẽ nhánh. Test chỉ cần tạo object rồi để nó ra khỏi phạm vi, khi đó destructor được gọi một lần.

C2 dự kiến = 0 / 0 (không có nhánh nào cần phủ, coi như đạt 100%).

**D. File test**

```cpp
// FILE: u0219_test.cc
#include "gtest/gtest.h"
#include "ceres/block_jacobi_preconditioner.h"

namespace ceres {
namespace internal {

// P1: START -> END (destructor không có điểm rẽ nhánh)
TEST(BlockSparseJacobiPreconditionerDestructorTest, P1_StartToEnd) {
  // Cấu trúc khối: 1 row block (size 1), 1 col block (size 1), 1 cell.
  auto* bs = new CompressedRowBlockStructure;

  Block col;
  col.size = 1;
  col.position = 0;
  bs->cols.push_back(col);

  CompressedRow row;
  row.block.size = 1;
  row.block.position = 0;
  Cell cell;
  cell.block_id = 0;
  cell.position = 0;
  row.cells.push_back(cell);
  bs->rows.push_back(row);

  // BlockSparseMatrix nhận quyền sở hữu bs.
  BlockSparseMatrix A(bs);
  A.SetZero();

  Preconditioner::Options options;

  {
    BlockSparseJacobiPreconditioner preconditioner(options, A);
  }  // destructor được gọi tại đây (node START -> END)
  SUCCEED();
}

}  // namespace internal
}  // namespace ceres
```

Lưu ý: test gọi `A.SetZero()` và `SUCCEED()` ngoài unit, chỉ để dữ liệu ma trận hợp lệ và test có một kết luận rõ ràng, không kiểm tra kết quả trả về. Các kiểu `CompressedRowBlockStructure`, `Block`, `CompressedRow`, `Cell` và `BlockSparseMatrix` được `block_jacobi_preconditioner.h` kéo vào qua `block_sparse_matrix.h` và `block_structure.h`. Tôi chưa biên dịch hay chạy file này, và chưa đối chiếu với mã nguồn Ceres 2.2.0 trong repo.