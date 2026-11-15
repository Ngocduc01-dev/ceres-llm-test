**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → END | node 1: đúng |
| P2 | START → 1 → 3 → END | node 1: sai |

Hàm không có vòng lặp nên không cần test số lần lặp.

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `size` ∈ [1, 5]; không gọi `SetUpperBound` nên `upper_bounds_` là null; `index` ∈ [0, size−1] | `size = 4`, `index = 2` |
| TC2 | P2 | `size` ∈ [1, 5]; phải gọi `SetUpperBound` để `upper_bounds_` khác null; `index` ∈ [0, size−1]; giá trị cận trên là số thực bất kỳ | `size = 3`, `index = 1`, cận trên `= 7.5` |

TC2 dùng `SetUpperBound(int, double)`, là method của chính class `ParameterBlock` trong `parameter_block.h`, chỉ để thiết lập trạng thái.

**C. Nhánh không test**

Không có nhánh nào bị bỏ. Cả hai nhánh của node 1 đều có test.

`C2 dự kiến = 2 / 2`

**D. File test**

```cpp
// FILE: u0484_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> 2 -> END (node 1: đúng)
TEST(ParameterBlockUpperBoundForParameterTest, TC1_NoUpperBounds) {
  double values[4] = {0.1, 0.2, 0.3, 0.4};
  ParameterBlock block(values, 4, 0);
  double result = block.UpperBoundForParameter(2);
  (void)result;  // Không kiểm tra kết quả trả về
}

// Path P2: START -> 1 -> 3 -> END (node 1: sai)
TEST(ParameterBlockUpperBoundForParameterTest, TC2_HasUpperBounds) {
  double values[3] = {1.0, 2.0, 3.0};
  ParameterBlock block(values, 3, 0);
  block.SetUpperBound(1, 7.5);
  double result = block.UpperBoundForParameter(1);
  (void)result;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
```