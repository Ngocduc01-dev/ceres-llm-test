**A. Test paths**

Unit không có điểm rẽ nhánh (0 điểm rẽ nhánh, 0 nhánh). CFG chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh nào (không có điểm rẽ nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `initial_cost`: số thực bất kỳ (không có điều kiện ràng buộc), chọn trong [0, 100]; `max_consecutive_nonmonotonic_steps`: số nguyên bất kỳ, chọn trong [0, 10] | `initial_cost` = 37.5 ; `max_consecutive_nonmonotonic_steps` = 5 |

**C. Nhánh không test**

Không có. Unit không có điểm rẽ nhánh và không có `CHECK`.

C2 dự kiến = 0 / 0 (tổng số nhánh bằng 0, node 1 là đoạn lệnh tuần tự duy nhất và được chạy qua ở TC1, nên coi như phủ 100%).

**D. File test**

```cpp
// FILE: u0433_test.cc
#include "gtest/gtest.h"
#include "ceres/trust_region_step_evaluator.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(TrustRegionStepEvaluatorConstructorTest, P1_SequentialInitializers) {
  const double initial_cost = 37.5;
  const int max_consecutive_nonmonotonic_steps = 5;
  TrustRegionStepEvaluator evaluator(initial_cost,
                                     max_consecutive_nonmonotonic_steps);
  (void)evaluator;
}

}  // namespace internal
}  // namespace ceres
```