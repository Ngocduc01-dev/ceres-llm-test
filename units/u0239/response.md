**A. Test paths**

Số điểm rẽ nhánh: 0, nên tổng số nhánh = 0. Chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh (node 1 chỉ gồm các member initializer `block_id`, `position`) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Constructor mặc định, không có tham số | Không có (chỉ tạo object `Cell cell;`) |

**C. Nhánh không test**

Không có. Unit không có điểm rẽ nhánh, không có vòng lặp và không có `CHECK`.

C2 dự kiến = 0 / 0 (không có nhánh nào; đường đi duy nhất P1 được chạy qua, tương đương phủ 100%).

Ghi chú: CFG khớp với mã nguồn (`Cell() = default;`). Các member `block_id` và `position` được khởi tạo bằng member initializer mặc định, nên không cần kiểm tra giá trị.

**D. File test**

```cpp
// FILE: u0239_test.cc
#include "gtest/gtest.h"
#include "ceres/block_structure.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(CellDefaultConstructor, TC1_DefaultConstruct) {
  Cell cell;
  (void)cell;
}

}  // namespace internal
}  // namespace ceres
```