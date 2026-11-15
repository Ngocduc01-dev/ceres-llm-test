**A. Test paths**

Hàm `Block()` là constructor mặc định, không có điểm rẽ nhánh (0 điểm rẽ nhánh, 0 nhánh).

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

Ghi chú: mã nguồn `Block() = default;` khớp với CFG. Node 1 là các member initializer của `size` và `position`.

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có đầu vào (constructor không tham số) | Không có |

**C. Nhánh không test**

Không có nhánh nào bị bỏ qua, vì hàm không có điểm rẽ nhánh và không có `CHECK`.

`C2 dự kiến = 0 / 0` (không có nhánh nào; mọi câu lệnh của hàm đều được chạy qua P1, tức là phủ 100% theo quy ước).

**D. File test**

```cpp
// FILE: u0237_test.cc
#include "gtest/gtest.h"
#include "ceres/block_structure.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(BlockDefaultConstructorTest, P1_DefaultConstruct) {
  Block block;
  (void)block;
}

}  // namespace internal
}  // namespace ceres
```