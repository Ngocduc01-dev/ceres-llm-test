**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh; chỉ một đường đi duy nhất qua node 1 (`delta_offset_ = delta_offset`) |

CFG khớp với mã nguồn (hàm một dòng, không có rẽ nhánh, không có vòng lặp, không có `CHECK`).

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `delta_offset`: mọi giá trị `int` (không có điều kiện ràng buộc); `user_state`: mảng 3 double; `size` = 3; `index` = 0 | `delta_offset` = 7 (chọn ngẫu nhiên, cố định); `size` = 3; `index` = 0 |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh nào, không có vòng lặp, không có `CHECK`.

`C2 dự kiến = 0 / 0` (không có nhánh; test chạy hết đường đi duy nhất START → 1 → END, tức phủ 100% câu lệnh).

**D. File test**

```cpp
// FILE: u0370_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ParameterBlockSetDeltaOffsetTest, TC1_AssignsDeltaOffset) {
  double values[3] = {1.0, 2.0, 3.0};
  ParameterBlock block(values, 3, 0);
  block.set_delta_offset(7);
}

}  // namespace internal
}  // namespace ceres
```