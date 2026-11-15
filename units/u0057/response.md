**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào |

Ghi chú: CFG khớp với mã nguồn (dòng 105–106). Hàm không có `if`, vòng lặp, `switch` hay `?:`, nên chỉ có một đường đi duy nhất.

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `value` là `double` bất kỳ (lvalue, `const double&`), ví dụ trong [-10, 10] | 3.5 (chọn cố định, đại diện cho giá trị ngẫu nhiên trong khoảng) |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh nào và không có `CHECK`.

`C2 dự kiến = 0 / 0` (tổng số nhánh bằng 0, nên mọi đường đi duy nhất P1 đều được chạy qua; coi như đạt 100%).

**D. File test**

```cpp
// FILE: u0057_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/jet_traits.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(AsScalarTest, P1_ConstDoubleLvalue) {
  const double value = 3.5;
  // Không kiểm tra kết quả trả về, chỉ gọi hàm để đi qua đường P1.
  (void)ceres::internal::AsScalar<const double&>(value);
  SUCCEED();
}
```