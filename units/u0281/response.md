**A. Test paths**

Hàm không có điểm rẽ nhánh (0 điểm rẽ nhánh, 0 nhánh, không có vòng lặp, không có `CHECK`), nên chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh nào (không có điểm rẽ nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `step_quality`: bất kỳ số thực (tham số không được dùng, vì đã comment `/*step_quality*/`); `options` của constructor: để mặc định | `step_quality` = 0.25; `options` mặc định |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh nên tổng số nhánh = 0. Một test TC1 đi hết đường đi duy nhất (node 1).
`C2 dự kiến = 0 / 0` (không có nhánh nào; toàn bộ câu lệnh ở node 1 đều được chạy, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0281_test.cc
#include "gtest/gtest.h"
#include "ceres/dogleg_strategy.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END
TEST(DoglegStrategyStepRejected, TC1_P1_SingleStatementPath) {
  TrustRegionStrategy::Options options;
  DoglegStrategy strategy(options);
  strategy.StepRejected(0.25);
}

}  // namespace internal
}  // namespace ceres
```