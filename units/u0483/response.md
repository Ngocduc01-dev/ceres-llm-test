**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → END | node 1: đúng |
| P2 | START → 1 → 3 → END | node 1: sai |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `lower_bounds_` chưa được đặt (không gọi `SetLowerBound`); `size` = 3; `index` trong [0, 2] | `size` = 3, `index` = 1 |
| TC2 | P2 | Gọi `SetLowerBound(index, giá trị)` trước để `lower_bounds_` khác `nullptr`; `size` = 3; `index` trong [0, 2] | `size` = 3, `index` = 1, lower bound = -2.5 |

**C. Nhánh không test**

- Không có nhánh nào không thể đi tới hoặc bị bỏ qua. Hàm không có vòng lặp và không có `CHECK`.
- CFG khớp với mã nguồn.
- Để đặt `lower_bounds_` khác `nullptr` (TC2), test dùng `SetLowerBound(int, double)`, một method public khác của `ParameterBlock`, vì hàm cần test không có cách nào khác để thiết lập trạng thái này. `SetLowerBound` có `CHECK_LT(index, size_)`, nên `index` = 1 < `size` = 3 luôn thoả.
- C2 dự kiến = 2 / 2 (dự kiến, chưa chạy thật)

**D. File test**

```cpp
// FILE: u0483_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

namespace ceres {
namespace internal {

// TC1 - P1: node 1: đúng (lower_bounds_ == nullptr) -> node 2 -> END
TEST(ParameterBlockLowerBoundForParameter, NoLowerBoundsSet) {
  double x[3] = {0.5, 1.5, 2.5};
  ParameterBlock block(x, 3, 0);
  volatile double result = block.LowerBoundForParameter(1);
  (void)result;
}

// TC2 - P2: node 1: sai (lower_bounds_ != nullptr) -> node 3 -> END
TEST(ParameterBlockLowerBoundForParameter, LowerBoundsSet) {
  double x[3] = {0.5, 1.5, 2.5};
  ParameterBlock block(x, 3, 0);
  block.SetLowerBound(1, -2.5);
  volatile double result = block.LowerBoundForParameter(1);
  (void)result;
}

}  // namespace internal
}  // namespace ceres
```