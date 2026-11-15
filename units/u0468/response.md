**A. Test paths**

Chỉ node 2 là điểm rẽ nhánh. Node 1 và node 3 là các đoạn lệnh chạy liền. Tổng số nhánh = 2.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → END | node 2: đúng (`num_parameters_ >= 1000`) |
| P2 | START → 1 → 2 → 3 → END | node 2: sai (`num_parameters_ < 1000`) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `num_parameters` ∈ [1000, 1100]; `use_approximate_eigenvalue_scaling` ∈ {true, false} | `num_parameters` = 1024, `use_approximate_eigenvalue_scaling` = true |
| TC2 | P2 | `num_parameters` ∈ [1, 5]; `use_approximate_eigenvalue_scaling` ∈ {true, false} | `num_parameters` = 3, `use_approximate_eigenvalue_scaling` = false |

**C. Nhánh không test**

Không có. Cả hai nhánh của node 2 đều đi tới được. Constructor không có `CHECK` và không có vòng lặp.

`C2 dự kiến = 2 / 2`

Lưu ý: nếu khi biên dịch báo không thấy class `BFGS` (vì class chỉ được định nghĩa trong `line_search_direction.cc`, không nằm trong header), cần biên dịch file test cùng với file `.cc` đó. Em giữ đúng các `#include` ở mục 3.3 như yêu cầu.

**D. File test**

```cpp
// FILE: u0468_test.cc
#include "gtest/gtest.h"
#include "ceres/line_search_direction.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> 2 (đúng: num_parameters_ >= 1000) -> 3 -> END
TEST(BFGSConstructorTest, TC1_LargeNumParametersLogsWarning) {
  const int num_parameters = 1024;
  const bool use_approximate_eigenvalue_scaling = true;
  BFGS bfgs(num_parameters, use_approximate_eigenvalue_scaling);
}

// P2: START -> 1 -> 2 (sai: num_parameters_ < 1000) -> 3 -> END
TEST(BFGSConstructorTest, TC2_SmallNumParametersNoWarning) {
  const int num_parameters = 3;
  const bool use_approximate_eigenvalue_scaling = false;
  BFGS bfgs(num_parameters, use_approximate_eigenvalue_scaling);
}

}  // namespace internal
}  // namespace ceres
```