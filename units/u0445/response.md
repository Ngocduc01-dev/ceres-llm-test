**Ghi chú:** CFG được dựng cho `ArraySelector<int, -1, 20>` (node 1 là `FixedArray(s)`), nhưng dòng 82 trong mã nguồn là constructor của bản đặc biệt hoá "vừa trong stack", chỉ có `CHECK_EQ(s, num_elements)`. Theo yêu cầu tin mã nguồn, nên test dùng `ArraySelector<int, 3, 20>` và `s = 3` để `CHECK_EQ` đúng. Tên node vẫn theo CFG (node 1).

**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh. `CHECK_EQ` đúng nên chương trình tiếp tục. |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `s == num_elements == 3` (chỉ một giá trị hợp lệ, không có khoảng) | `s = 3` |

**C. Nhánh không test**

- Nhánh `CHECK_EQ` sai (`s != num_elements`): không test (làm chương trình dừng). Nhánh này không tính vào tổng số nhánh.
- Không có vòng lặp.
- `C2 dự kiến = 0 / 0` (unit không có điểm rẽ nhánh, đường duy nhất P1 được chạy qua, tương đương 100%).

**D. File test**

```cpp
// FILE: u0445_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/array_selector.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (CHECK_EQ đúng, s == num_elements == 3)
TEST(ArraySelectorConstructorTest, P1_SizeEqualsNumElements) {
  ArraySelector<int, 3, 20> selector(3);
  (void)selector;
}

}  // namespace internal
}  // namespace ceres
```