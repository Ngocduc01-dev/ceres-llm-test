**A. Test paths**

Unit không có điểm rẽ nhánh nên chỉ có một đường đi.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `elimination_groups[0]` = số khối E, phải từ 1 đến 1 vì ma trận có 1 khối E. Ma trận: 1 hàng khối cỡ 2, 1 khối E cỡ 2 và 1 khối F cỡ 2. Giá trị phần tử nằm trong [1, 5], cố định bằng seed. | `elimination_groups = {1}`, ma trận 2×4, giá trị sinh bằng `std::mt19937(42)` |

Ghi chú: `A_` chỉ được tạo trong `Init(...)`. Nếu gọi `num_cols()` khi chưa `Init` thì `A_` là null và chương trình sẽ lỗi. Vì vậy test phải gọi `Init` trước, rồi mới gọi `num_cols()` đúng một lần.

**C. Nhánh không test**

Không có nhánh nào, vì unit không có điểm rẽ nhánh và cũng không có `CHECK`.

`C2 dự kiến = 0 / 0` (không có nhánh nào cần phủ; node 1 được chạy qua nên đạt 100%).

**D. File test**

```cpp
// FILE: u0313_test.cc
#include <memory>
#include <random>
#include <vector>

#include "gtest/gtest.h"
#include "ceres/implicit_schur_complement.h"
#include "ceres/partitioned_matrix_view.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ImplicitSchurComplementNumColsTest, P1_ReturnNumColsF) {
  // Ma trận khối: 1 hàng khối (cỡ 2), khối E (cột 0, cỡ 2), khối F (cột 2, cỡ 2).
  auto* bs = new CompressedRowBlockStructure;
  bs->cols.push_back(Block(2, 0));  // khối E
  bs->cols.push_back(Block(2, 2));  // khối F

  bs->rows.resize(1);
  bs->rows[0].block = Block(2, 0);
  bs->rows[0].cells.push_back(Cell(0, 0));  // cell E, offset 0
  bs->rows[0].cells.push_back(Cell(1, 4));  // cell F, offset 4

  BlockSparseMatrix A(bs);  // A nhận quyền sở hữu bs

  // Giá trị cố định nhờ seed 42, nằm trong [1, 5].
  std::mt19937 gen(42);
  std::uniform_real_distribution<double> dist(1.0, 5.0);
  double* values = A.mutable_values();
  for (int i = 0; i < A.num_nonzeros(); ++i) {
    values[i] = dist(gen);
  }

  std::vector<double> D(A.num_cols(), 1.0);
  std::vector<double> b(A.num_rows(), 1.0);

  LinearSolver::Options options;
  options.elimination_groups.push_back(1);  // 1 khối E

  ImplicitSchurComplement isc(options);
  isc.Init(A, D.data(), b.data());

  // Gọi unit một lần, không kiểm tra kết quả.
  isc.num_cols();
}

}  // namespace internal
}  // namespace ceres
```