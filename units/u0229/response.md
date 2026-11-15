**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có điểm rẽ nhánh nên không có nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Kích thước block: 1 đến 5. Số block: 1 đến 2. `block_pairs` gồm các cặp (i, i) hợp lệ. `context`: `nullptr`. `num_threads`: 1. | Block(2,0), Block(3,2). `block_pairs` = {(0,0), (1,1)}. `context` = `nullptr`. `num_threads` = 1. |

**C. Nhánh không test**

Không có nhánh nào cần ghi vì hàm không có điểm rẽ nhánh. Destructor `= default` chỉ có một đường START → END, và test TC1 chạy qua nó khi object ra khỏi phạm vi.

Lưu ý: CFG khớp với mã nguồn (dòng 70 là `= default`).

C2 dự kiến = 0 / 0 (tổng số nhánh = 0, mọi đường đi đều đã được phủ nên coi như 100%)

**D. File test**

```cpp
// FILE: u0229_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_sparse_matrix.h"

#include <set>
#include <utility>
#include <vector>

namespace ceres {
namespace internal {

// P1: START -> END
TEST(BlockRandomAccessSparseMatrixDestructorTest, DestroyObject_P1) {
  std::vector<Block> blocks;
  blocks.emplace_back(2, 0);
  blocks.emplace_back(3, 2);

  std::set<std::pair<int, int>> block_pairs;
  block_pairs.insert(std::make_pair(0, 0));
  block_pairs.insert(std::make_pair(1, 1));

  {
    BlockRandomAccessSparseMatrix matrix(blocks, block_pairs, nullptr, 1);
  }  // destructor ~BlockRandomAccessSparseMatrix() được gọi tại đây
  SUCCEED();
}

}  // namespace internal
}  // namespace ceres
```