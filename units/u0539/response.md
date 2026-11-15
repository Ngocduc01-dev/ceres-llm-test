**A. Test paths**

Hàm có 3 điểm rẽ nhánh (node 2, 4, 7), tổng cộng 6 nhánh. Hàm không có vòng lặp. Không có `CHECK` trong hàm.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → 9 → END | node 2: đúng, node 4: đúng, node 7: đúng |
| P2 | START → 1 → 2 → 4 → 6 → 7 → 9 → END | node 2: sai, node 4: sai, node 7: sai |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `absolute_error = nullptr`, `relative_error = nullptr`, `x == 0` (hoặc `y == 0`), `y` ∈ [1, 10], `relative_precision` ∈ [1e-6, 1e-1] | `x = 0.0`, `y = 3.7`, `relative_precision = 1e-3`, cả hai con trỏ là `nullptr` |
| TC2 | P2 | Cả hai con trỏ khác `nullptr`, `x` ∈ [1, 10], `y` ∈ [1, 10] (khác 0), `relative_precision` ∈ [1e-6, 1e-1] | `x = 5.2`, `y = 8.4`, `relative_precision = 1e-3`, hai con trỏ trỏ tới hai biến `double` cục bộ |

**C. Nhánh không test**

Không có nhánh nào bị bỏ. Cả 6 nhánh đều đi tới được.

C2 dự kiến = 6 / 6

**D. File test**

```cpp
// FILE: u0539_test.cc
#include "ceres/is_close.h"
#include "gtest/gtest.h"

namespace ceres {
namespace internal {

// Path P1: node 2: đúng, node 4: đúng, node 7: đúng
TEST(IsCloseTest, NullErrorPointersAndOneInputIsZero) {
  const double x = 0.0;
  const double y = 3.7;
  const double relative_precision = 1e-3;
  bool result = IsClose(x, y, relative_precision, nullptr, nullptr);
  (void)result;
}

// Path P2: node 2: sai, node 4: sai, node 7: sai
TEST(IsCloseTest, NonNullErrorPointersAndNonZeroInputs) {
  const double x = 5.2;
  const double y = 8.4;
  const double relative_precision = 1e-3;
  double relative_error = 0.0;
  double absolute_error = 0.0;
  bool result =
      IsClose(x, y, relative_precision, &relative_error, &absolute_error);
  (void)result;
}

}  // namespace internal
}  // namespace ceres
```