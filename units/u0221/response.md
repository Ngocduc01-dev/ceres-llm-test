**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `blocks`: 1 đến 2 block, mỗi block có size từ 1 đến 5. `context`: `nullptr` (với `num_threads` = 1 thì không dùng đến). `num_threads` = 1. | 2 block có size 2 và 3 (vị trí 0 và 2). `context` = `nullptr`. `num_threads` = 1. |

**C. Nhánh không test**

Không có. Hàm huỷ là `= default`, nên không có điểm rẽ nhánh nào.

Ghi chú: nếu `ContextImpl` không có sẵn qua `#include` ở mục 3.3 thì phải bỏ qua kiểu này. Vì vậy test dùng `nullptr`.

`C2 dự kiến = 0 / 0` (tổng số nhánh là 0, nên coi như đạt 100%; dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0221_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_dense_matrix.h"

#include <memory>
#include <vector>

// Path P1: START -> END (không có điểm rẽ nhánh)
TEST(BlockRandomAccessDenseMatrixDestructorTest, P1_StartToEnd) {
  std::vector<ceres::internal::Block> blocks;
  blocks.emplace_back(2, 0);
  blocks.emplace_back(3, 2);

  std::unique_ptr<ceres::internal::BlockRandomAccessDenseMatrix> matrix(
      new ceres::internal::BlockRandomAccessDenseMatrix(
          blocks, nullptr, 1));

  // Gọi destructor đúng một lần.
  matrix.reset();
}
```