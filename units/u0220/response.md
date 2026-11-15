**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Ma trận A có số hàng và số cột từ 1 đến 5. Một block kích thước bằng số cột. | A là ma trận 2×2, tối đa 4 phần tử khác 0, một block kích thước 2. Đối tượng được tạo rồi huỷ khi ra khỏi phạm vi. |

**C. Nhánh không test**

Không có nhánh nào, vì unit không có điểm rẽ nhánh. Mẫu số của C2 là 0, nên coi như phủ 100% khi START → END được chạy.

`C2 dự kiến = 0 / 0 (không có nhánh; đường START → END được chạy qua 1 test)`

Ghi chú: CFG khớp với mã nguồn. Destructor là `= default` nên việc gọi hàm chính là lúc đối tượng bị huỷ.

**D. File test**

```cpp
// FILE: u0220_test.cc
#include "gtest/gtest.h"
#include "ceres/block_jacobi_preconditioner.h"

namespace ceres {
namespace internal {

// TC1 - P1: START -> END (destructor không có nhánh)
TEST(BlockCRSJacobiPreconditionerDestructorTest, DestroyObject) {
  CompressedRowSparseMatrix A(2, 2, 4);
  A.mutable_row_blocks()->push_back(Block(2, 0));
  A.mutable_col_blocks()->push_back(Block(2, 0));

  Preconditioner::Options options;
  {
    BlockCRSJacobiPreconditioner preconditioner(options, A);
  }  // destructor được gọi tại đây
  SUCCEED();
}

}  // namespace internal
}  // namespace ceres
```