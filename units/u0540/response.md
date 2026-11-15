**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → END | node 1: đúng, node 2: đúng |
| P2 | START → 1 → 2 → 4 → 5 → 6 → END | node 1: đúng, node 2: sai, node 4: đúng |
| P3 | START → 1 → 2 → 4 → 6 → END | node 1: đúng, node 2: sai, node 4: sai |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | size = 3, index ∈ [0, 2], upper_bound ≥ DBL_MAX, `upper_bounds_` chưa cấp phát (object mới) | index = 2, upper_bound = `std::numeric_limits<double>::max()` |
| TC2 | P2 | size = 3, index ∈ [0, 2], upper_bound < DBL_MAX, `upper_bounds_` chưa cấp phát | index = 0, upper_bound = 5.0 |
| TC3 | P3 | size = 3, index ∈ [0, 2], `upper_bounds_` đã cấp phát (có 1 lệnh gọi chuẩn bị trước), upper_bound bất kỳ | chuẩn bị: index = 0, upper_bound = 3.5. Gọi unit: index = 1, upper_bound = 7.25 |

Các giá trị được cố định sẵn trong code, không dùng hàm sinh số ngẫu nhiên.

**C. Nhánh không test**

- Nhánh sai của `CHECK_LT(index, size_)` ở node 1: không test (làm chương trình dừng).
- Không có nhánh nào không thể đi tới.
- Lưu ý ở TC3: `upper_bounds_` là thành viên private và không có hàm nào khác để cấp phát nó. Vì vậy TC3 phải gọi `SetUpperBound` một lần để chuẩn bị (đi theo P2), rồi mới gọi lần thứ hai để đi theo P3.
- C2 dự kiến = 4 / 4. Tổng số nhánh là 2 điểm rẽ nhánh × 2. Đây là số dự kiến, chưa chạy thật.

**D. File test**

```cpp
// FILE: u0540_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

// Path P1: START -> 1 -> 2 -> 3 -> END (node 1: đúng, node 2: đúng)
TEST(ParameterBlockSetUpperBound, P1_MaxBoundWithoutExistingBounds) {
  double state[3] = {0.1, 0.2, 0.3};
  ceres::internal::ParameterBlock block(state, 3, 0);
  block.SetUpperBound(2, std::numeric_limits<double>::max());
}

// Path P2: START -> 1 -> 2 -> 4 -> 5 -> 6 -> END (node 1: đúng, node 2: sai, node 4: đúng)
TEST(ParameterBlockSetUpperBound, P2_AllocateBoundsThenSet) {
  double state[3] = {0.1, 0.2, 0.3};
  ceres::internal::ParameterBlock block(state, 3, 0);
  block.SetUpperBound(0, 5.0);
}

// Path P3: START -> 1 -> 2 -> 4 -> 6 -> END (node 1: đúng, node 2: sai, node 4: sai)
TEST(ParameterBlockSetUpperBound, P3_BoundsAlreadyAllocated) {
  double state[3] = {0.1, 0.2, 0.3};
  ceres::internal::ParameterBlock block(state, 3, 0);
  // Chuẩn bị: cấp phát upper_bounds_ (lệnh gọi này không thuộc path P3).
  block.SetUpperBound(0, 3.5);
  // Lệnh gọi được kiểm thử theo P3.
  block.SetUpperBound(1, 7.25);
}
```