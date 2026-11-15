**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh. Node 1 (`return AsScalar(f) != AsScalar(g)`) chạy tuần tự. |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f` là `Jet<double, 16>` với phần scalar là một số double bất kỳ. `g` là `double` bất kỳ. Không có điều kiện ràng buộc. | `f = Jet<double, 16>(2.5)`, `g = 3.7` |

**C. Nhánh không test**

- Không có. Hàm không có điểm rẽ nhánh nên không có nhánh nào bị bỏ sót.
- `C2 dự kiến = 0 / 0` (tổng số nhánh = 0; node 1 được chạy qua, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0095_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace {

// Path P1: START -> 1 -> END
TEST(JetNotEqualOperator, JetWithScalarStraightLine) {
  const Jet<double, 16> f(2.5);
  const double g = 3.7;
  const bool result = (f != g);
  (void)result;  // Không kiểm tra kết quả trả về.
}

}  // namespace
}  // namespace ceres
```