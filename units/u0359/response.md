**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm rẽ nhánh, 0 nhánh) và không có vòng lặp. Chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `user_state`: con trỏ tới mảng double hợp lệ (1–5 phần tử); `size` từ 1 đến 5; `index` từ 0 đến 5 | mảng `{1.5, 2.5, 3.5}`, `size = 3`, `index = 2` |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh nên không có nhánh nào cần test hoặc bị loại.

`C2 dự kiến = 0 / 0` (không có nhánh; test đi qua node 1 duy nhất nên toàn bộ hàm được chạy, tức 100% theo quy ước).

**D. File test**

```cpp
// FILE: u0359_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

namespace ceres {
namespace internal {

// TC1 - Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ParameterBlockUserStateTest, ReturnsUserState) {
  double values[3] = {1.5, 2.5, 3.5};
  ParameterBlock block(values, 3, 2);
  const double* state = block.user_state();
  (void)state;  // Không kiểm tra kết quả trả về theo yêu cầu.
}

}  // namespace internal
}  // namespace ceres
```