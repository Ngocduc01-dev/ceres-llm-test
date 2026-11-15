**A. Test paths**

Unit không có điểm rẽ nhánh nên chỉ có 1 đường đi. CFG khớp với mã nguồn.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `elimination_groups[0]` = 1; ma trận khối có 3 khối cột cỡ 1 và 2 khối hàng cỡ 1; `A_` phải khác null nên bắt buộc gọi `Init` trước `num_rows()` | `elimination_groups = {1}`; cột E = 1, cột F = 2; `D = nullptr`; `b = {1.0, 2.0}` (cố định, không dùng random) |

**C. Nhánh không test**

Không có nhánh nào bị bỏ. `C2 dự kiến = 0 / 0` (không có điểm rẽ nhánh, nên đường đi duy nhất P1 phủ toàn bộ node, tương đương 100%).

Lưu ý: `A_` chỉ được tạo trong `Init(...)`. Ba `#include` ở mục 3.3 có thể chưa kéo vào định nghĩa đầy đủ của `BlockSparseMatrix`. Nếu biên dịch lỗi ở chỗ này, cần thêm `#include "ceres/block_sparse_matrix.h"`.

**D. File test**

```cpp
// FILE: u0312_test.cc
#include "gtest/gtest.h"
#include "ceres/implicit_schur_complement.h"
#include "ceres/partitioned_matrix_view.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có nhánh)
TEST(ImplicitSchurComplementNumRows, TC1_P1_ReturnNumColsF) {
  // Ma trận khối: 2 hàng, 3 cột (cột 0 là khối E, cột 1-2 là khối F).
  auto* bs = new CompressedRowBlockStructure;
  bs->cols.push_back(Block(1, 0));
  bs->cols.push_back(Block(1, 1));
  bs->cols.push_back(Block(1, 2));

  bs->rows.resize(2);
  bs->rows[0].block = Block(1, 0);
  bs->rows[0].cells.push_back(Cell(0, 0));
  bs->rows[0].cells.push_back(Cell(1, 1));

  bs->rows[1].block = Block(1, 1);
  bs->rows[1].cells.push_back(Cell(0, 2));
  bs->rows[1].cells.push_back(Cell(2, 3));

  BlockSparseMatrix A(bs);  // A sở hữu bs

  LinearSolver::Options options;
  options.elimination_groups.push_back(1);

  const double b[2] = {1.0, 2.0};

  ImplicitSchurComplement isc(options);
  isc.Init(A, nullptr, b);

  // Không kiểm tra kết quả trả về.
  isc.num_rows();
}

}  // namespace internal
}  // namespace ceres
```