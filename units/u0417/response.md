**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Số row block: 2–5. Số col block: 2–5. Kích thước block: 1–3. `subset_preconditioner_start_row_block` phải nhỏ hơn số row block, tức từ 0 đến (số row block − 1). Seed cố định. | 3 row block, 3 col block, kích thước block 2, mật độ 1.0, `start_row_block = 1`, seed 42, `EIGEN_SPARSE` |

**C. Nhánh không test:** không có, vì hàm không có điểm rẽ nhánh.
`C2 dự kiến = 0 / 0` (tổng số nhánh bằng 0, coi như đạt 100%; test chỉ cần chạy qua START → END).

Ghi chú: Constructor cần một `BlockSparseMatrix`. Để tạo ma trận này, tôi thêm `#include "ceres/block_sparse_matrix.h"` và `<random>` ngoài các include ở mục 3.3. Tôi chưa biên dịch hay chạy file test.

**D. File test**

```cpp
// FILE: u0417_test.cc
#include <random>

#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/subset_preconditioner.h"

namespace ceres {
namespace internal {

// Path P1: START -> END (hàm không có điểm rẽ nhánh)
TEST(SubsetPreconditionerDestructorTest, TC1_P1_StartToEnd) {
  std::mt19937 prng(42);

  BlockSparseMatrix::RandomMatrixOptions matrix_options;
  matrix_options.num_row_blocks = 3;
  matrix_options.min_row_block_size = 2;
  matrix_options.max_row_block_size = 2;
  matrix_options.num_col_blocks = 3;
  matrix_options.min_col_block_size = 2;
  matrix_options.max_col_block_size = 2;
  matrix_options.block_density = 1.0;

  std::unique_ptr<BlockSparseMatrix> A =
      BlockSparseMatrix::CreateRandomMatrix(matrix_options, prng);

  Preconditioner::Options options;
  options.subset_preconditioner_start_row_block = 1;
  options.sparse_linear_algebra_library_type = EIGEN_SPARSE;

  // Tạo object trên heap rồi delete để gọi destructor đúng một lần.
  SubsetPreconditioner* preconditioner =
      new SubsetPreconditioner(options, *A);
  delete preconditioner;
}

}  // namespace internal
}  // namespace ceres
```