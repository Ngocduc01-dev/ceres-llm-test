**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `n` từ 0 đến 20 (không có điều kiện đường đi; chọn n ≤ 20 để dùng bộ nhớ inline của `FixedArray<int, 20>`) | `n = 3` (chọn ngẫu nhiên với seed cố định, ghi sẵn giá trị) |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh và không có `CHECK`, nên tổng số nhánh là 0 và một test đi hết path P1.
`C2 dự kiến = 0 / 0` (không có nhánh nào; mọi câu lệnh, gồm node 1, đều được chạy, tức C1 = 100%).

Ghi chú: CFG khớp với mã nguồn. `Storage` là class lồng nằm trong phần `private` của `FixedArray`, nên file test dùng `#define private public` sau khi đã include các header chuẩn, để tạo được object `Storage` mà không sửa mã nguồn Ceres.

**D. File test**

```cpp
// FILE: u0053_test.cc
#include <algorithm>
#include <array>
#include <cstddef>
#include <iterator>
#include <limits>
#include <memory>
#include <new>
#include <tuple>
#include <type_traits>
#include <utility>

#include "gtest/gtest.h"

#define private public
#include "ceres/internal/fixed_array.h"
#undef private

namespace ceres {
namespace internal {

// P1: START -> 1 -> END
TEST(FixedArrayStorageSizeTest, TC1_P1_Node1_Return) {
  using Array = FixedArray<int, 20>;
  const Array::size_type n = 3;  // n trong [0, 20], chọn với seed cố định
  Array::allocator_type alloc;
  Array::Storage storage(n, alloc);
  storage.size();
}

}  // namespace internal
}  // namespace ceres
```