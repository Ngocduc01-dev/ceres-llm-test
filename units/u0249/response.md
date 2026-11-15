**A. Test paths**

Destructor `= default` không có điểm rẽ nhánh nào (0 điểm rẽ nhánh, 0 nhánh). Chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có nhánh nào (không có điểm rẽ nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `num_parameters`: 1 đến 5; `internal_parameters`, `user_parameters`: mảng double có `num_parameters` phần tử, giá trị bất kỳ | `num_parameters` = 3 (seed cố định 0 nên mỗi lần chạy ra cùng giá trị); các mảng gồm 3 phần tử |

**C. Nhánh không test**

Không có nhánh nào bị bỏ qua. Hàm không có điểm rẽ nhánh và không có `CHECK`.

`C2 dự kiến = 0 / 0` (tổng số nhánh = 0, nên mọi nhánh đều được phủ; coi như 100%).

**D. File test**

```cpp
// FILE: u0249_test.cc
#include <random>

#include "gtest/gtest.h"
#include "ceres/callbacks.h"

// Path P1: START -> END (không có điểm rẽ nhánh)
TEST(GradientProblemSolverStateUpdatingCallbackDestructorTest, TC1_P1_DefaultDestructor) {
  std::mt19937 rng(0);
  std::uniform_int_distribution<int> size_dist(1, 5);
  std::uniform_real_distribution<double> value_dist(-10.0, 10.0);

  const int num_parameters = size_dist(rng);
  double internal_parameters[5];
  double user_parameters[5];
  for (int i = 0; i < 5; ++i) {
    internal_parameters[i] = value_dist(rng);
    user_parameters[i] = value_dist(rng);
  }

  // Tạo object trên heap rồi huỷ để gọi destructor đúng một lần.
  auto* callback =
      new ceres::internal::GradientProblemSolverStateUpdatingCallback(
          num_parameters, internal_parameters, user_parameters);
  delete callback;
}
```