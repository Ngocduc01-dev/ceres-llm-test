**A. Test paths**

CFG khác với mã nguồn. CFG dựng cho `ArraySelector<int, -1, 20>` (dynamic, nền `FixedArray`), còn dòng 88–90 thuộc specialization dùng `std::vector<T>` (`num_elements != -1` và `num_elements > max_num_elements_on_stack`). Theo yêu cầu, tôi tin mã nguồn. Constructor này không có điểm rẽ nhánh, chỉ có `CHECK_EQ`, và `CHECK_EQ` không được tính.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh. `CHECK_EQ(s, num_elements)` đúng. |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Template `<int, 5, 2>` (5 > 2 và không phải dynamic, nên chọn specialization `std::vector`). `s` phải bằng `num_elements`, tức là `s = 5`. | `s = 5` |

**C. Nhánh không test**

- Nhánh `CHECK_EQ` sai (`s != num_elements`): không test (làm chương trình dừng).
- Vòng lặp: không có.

`C2 dự kiến = 0 / 0` (không có điểm rẽ nhánh nên tổng số nhánh là 0; unit được phủ hoàn toàn bởi TC1).

**D. File test**

```cpp
// FILE: u0446_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/array_selector.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (CHECK_EQ(s, num_elements) đúng)
TEST(ArraySelectorConstructorTest, VectorSpecializationSizeMatches) {
  ArraySelector<int, 5, 2> selector(5);
}

}  // namespace internal
}  // namespace ceres
```