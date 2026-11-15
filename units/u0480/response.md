**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 3 → END | node 1: sai (`upper_bounds_ == nullptr`) |
| P2 | START → 1 → 2 → 3 → END | node 1: đúng (`upper_bounds_ != nullptr`) |

Hàm không có vòng lặp và không có `CHECK`, nên không cần test lặp.

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `size` ∈ [1,5]; không gọi `SetUpperBound` (để `upper_bounds_` là null); `index` ∈ [0, size−1] | `size`=3, `index`=2 |
| TC2 | P2 | `size` ∈ [1,5]; gọi `SetUpperBound(index, v)` trước để `upper_bounds_` khác null; `index` ∈ [0, size−1]; `v` là số thực bất kỳ | `size`=3, `index`=1, `v`=4.5 |

Trong TC2, `SetUpperBound` (có trong `parameter_block.h`) chỉ dùng để chuẩn bị dữ liệu. Unit `UpperBound` vẫn chỉ được gọi một lần trong mỗi test.

**C. Nhánh không test**

Không có nhánh nào bị bỏ.

C2 dự kiến = 2 / 2

**D. File test**

```cpp
// FILE: u0480_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> 3 -> END (node 1: sai, upper_bounds_ == nullptr)
TEST(ParameterBlockUpperBoundTest, TC1_NoUpperBounds) {
  double values[3] = {1.0, 2.0, 3.0};
  ParameterBlock block(values, 3, 0);
  double result = block.UpperBound(2);
  (void)result;
}

// P2: START -> 1 -> 2 -> 3 -> END (node 1: đúng, upper_bounds_ != nullptr)
TEST(ParameterBlockUpperBoundTest, TC2_WithUpperBounds) {
  double values[3] = {1.0, 2.0, 3.0};
  ParameterBlock block(values, 3, 0);
  block.SetUpperBound(1, 4.5);
  double result = block.UpperBound(1);
  (void)result;
}

}  // namespace internal
}  // namespace ceres
```