**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm rẽ nhánh, 0 nhánh). Chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `options.initial_radius` > 0 (constructor gán `radius_` từ `initial_radius`); các trường khác của `Options` để mặc định | `initial_radius` = 1e4 (giá trị mặc định của Options, không cần gán) |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh nên tổng số nhánh là 0, không có nhánh nào bị bỏ qua.

`C2 dự kiến = 0 / 0` (không có nhánh; toàn bộ câu lệnh node 1 được chạy qua, tức đạt 100% theo quy ước).

**D. File test**

```cpp
// FILE: u0283_test.cc
#include "gtest/gtest.h"
#include "ceres/dogleg_strategy.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(DoglegStrategyRadiusTest, TC1_ReturnRadius) {
  TrustRegionStrategy::Options options;
  DoglegStrategy strategy(options);
  strategy.Radius();
}

}  // namespace internal
}  // namespace ceres
```