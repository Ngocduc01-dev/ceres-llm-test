**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh (0 điểm rẽ nhánh, 0 nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `num_parameters`: 1 đến 5 (không có điều kiện ràng buộc); `internal_parameters`: mảng `double` có `num_parameters` phần tử; `user_parameters`: mảng `double` có `num_parameters` phần tử | `num_parameters = 3`; `internal_parameters = {0.5, 1.5, 2.5}`; `user_parameters = {0.0, 0.0, 0.0}` |

**C. Nhánh không test**

Không có nhánh nào (unit không có điểm rẽ nhánh, không có vòng lặp, không có `CHECK`).
`C2 dự kiến = 0 / 0` (tổng số nhánh bằng 0; test chỉ đi qua node 1 để đạt phủ toàn bộ câu lệnh).

**D. File test**

```cpp
// FILE: u0248_test.cc
#include "gtest/gtest.h"
#include "ceres/callbacks.h"

// Path P1: START -> 1 -> END
TEST(GradientProblemSolverStateUpdatingCallbackTest, ConstructorP1) {
  double internal_parameters[3] = {0.5, 1.5, 2.5};
  double user_parameters[3] = {0.0, 0.0, 0.0};
  ceres::internal::GradientProblemSolverStateUpdatingCallback callback(
      3, internal_parameters, user_parameters);
}
```