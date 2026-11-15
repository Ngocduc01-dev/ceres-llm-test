**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 3 → END | node 1: sai (`lower_bounds_ == nullptr`) |
| P2 | START → 1 → 2 → 3 → END | node 1: đúng (`lower_bounds_ != nullptr`) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `size` ∈ [1, 5]; không gọi `SetLowerBound`, nên `lower_bounds_` là null; `index` ∈ [0, size−1] | `size` = 3, `index` = 2 |
| TC2 | P2 | `size` ∈ [1, 5]; phải gọi `SetLowerBound` trước để `lower_bounds_` khác null; `index` ∈ [0, size−1] | `size` = 4, `index` = 1, lower bound = -2.5 |

**C. Nhánh không test**

- Không có nhánh nào bị bỏ. Node 2 chỉ là `operator[]` của con trỏ, không có điều kiện `CHECK`.
- Mã nguồn khớp với CFG.
- Để `lower_bounds_` khác null, TC2 gọi `SetLowerBound(int, double)` của cùng class `ParameterBlock`. Hàm này không nằm trong mục 3.3 nhưng là method có sẵn trong `parameter_block.h`.
- `C2 dự kiến = 2 / 2` (dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0481_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> 3 -> END (node 1: sai, lower_bounds_ == nullptr)
TEST(ParameterBlockLowerBoundTest, NoLowerBoundsAllocated) {
  double values[3] = {0.5, 1.5, -0.5};
  ParameterBlock block(values, 3, -1);
  double result = block.LowerBound(2);
  (void)result;
}

// Path P2: START -> 1 -> 2 -> 3 -> END (node 1: đúng, lower_bounds_ != nullptr)
TEST(ParameterBlockLowerBoundTest, LowerBoundsAllocated) {
  double values[4] = {0.1, 0.2, 0.3, 0.4};
  ParameterBlock block(values, 4, -1);
  block.SetLowerBound(1, -2.5);
  double result = block.LowerBound(1);
  (void)result;
}

}  // namespace internal
}  // namespace ceres
```