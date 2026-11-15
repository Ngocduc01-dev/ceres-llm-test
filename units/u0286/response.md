**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có điểm rẽ nhánh nào (hàm chỉ có 1 câu lệnh `return subspace_basis_;`) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Hàm không có tham số. Object tạo bởi `TrustRegionStrategy::Options` mặc định (không ràng buộc giá trị). | Options mặc định (không gán trường nào) |

**C. Nhánh không test**

Không có nhánh nào (hàm có 0 điểm rẽ nhánh, không có `CHECK`).

`C2 dự kiến = 0 / 0` (không có nhánh; path P1 duy nhất START → END được chạy, nên coi là phủ 100%).

**D. File test**

```cpp
// FILE: u0286_test.cc
#include "gtest/gtest.h"
#include "ceres/dogleg_strategy.h"

namespace ceres {
namespace internal {

// Path P1: START -> END (không có điểm rẽ nhánh)
TEST(DoglegStrategySubspaceBasisTest, P1_ReturnsSubspaceBasis) {
  TrustRegionStrategy::Options options;
  DoglegStrategy strategy(options);
  Matrix basis = strategy.subspace_basis();
  (void)basis;
}

}  // namespace internal
}  // namespace ceres
```