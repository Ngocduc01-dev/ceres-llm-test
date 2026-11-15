**A. Test paths**

Hàm `~BlockRandomAccessDiagonalMatrix()` là destructor `= default`. Nó không có điểm rẽ nhánh và không có vòng lặp. CFG chỉ có `START → END` (không có node đánh số).

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `blocks`: 1–5 block, mỗi block có size 1–5; `context`: `nullptr` (constructor không dùng đến); `num_threads` ≥ 1 | 2 block: size 2 tại vị trí 0 và size 3 tại vị trí 2; `context = nullptr`; `num_threads = 1` |

**C. Nhánh không test**

Không có nhánh nào bị bỏ qua, vì hàm không có điểm rẽ nhánh. Tổng số nhánh là 0 nên C2 không có mẫu số, coi như đạt 100%.

`C2 dự kiến = 0 / 0` (không có nhánh nào cần phủ, coi như 100%; dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0226_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_diagonal_matrix.h"

namespace ceres {
namespace internal {

// P1: START -> END (destructor không có nhánh)
TEST(BlockRandomAccessDiagonalMatrixDestructorTest, DestroyObject) {
  std::vector<Block> blocks;
  blocks.emplace_back(2, 0);
  blocks.emplace_back(3, 2);

  // Object được tạo trên heap rồi huỷ tường minh để gọi destructor đúng một lần.
  BlockRandomAccessDiagonalMatrix* matrix =
      new BlockRandomAccessDiagonalMatrix(blocks, nullptr, 1);
  delete matrix;
}

}  // namespace internal
}  // namespace ceres
```