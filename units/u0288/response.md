**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có điểm rẽ nhánh nào |

CFG khớp với mã nguồn: hàm chỉ có một câu lệnh `return subspace_B_;`. Không có vòng lặp và không có `CHECK`.

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có tham số đầu vào. Object được tạo từ `TrustRegionStrategy::Options` mặc định. | Options mặc định (`linear_solver = nullptr`) |

**C. Nhánh không test:** không có.
`C2 dự kiến = 0 / 0` (hàm không có điểm rẽ nhánh nên mọi đường đi đều được phủ, coi như 100%; dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0288_test.cc
#include "gtest/gtest.h"
#include "ceres/dogleg_strategy.h"

namespace ceres {
namespace internal {

// Path P1: START -> END
TEST(DoglegStrategySubspaceBTest, P1_ReturnSubspaceB) {
  TrustRegionStrategy::Options options;
  DoglegStrategy strategy(options);
  Matrix b = strategy.subspace_B();
  (void)b;
}

}  // namespace internal
}  // namespace ceres
```