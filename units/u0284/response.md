**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Hàm không có tham số. Object được tạo bằng `TrustRegionStrategy::Options` mặc định, nên không có ràng buộc nào từ điều kiện đường đi. | Options mặc định, không đổi trường nào |

**C. Nhánh không test**

Không có. Hàm có 0 điểm rẽ nhánh nên không có nhánh nào bị bỏ sót. Không cần test vòng lặp vì hàm không có vòng lặp.

`C2 dự kiến = 0 / 0` (không có nhánh nào; đường START → END được phủ bởi TC1, tức 100% theo quy ước).

**D. File test**

```cpp
// FILE: u0284_test.cc
#include "gtest/gtest.h"
#include "ceres/dogleg_strategy.h"

namespace ceres {
namespace internal {

// P1: START -> END (không có điểm rẽ nhánh)
TEST(DoglegStrategyGradientTest, P1_StartToEnd) {
  TrustRegionStrategy::Options options;
  DoglegStrategy strategy(options);
  Vector g = strategy.gradient();
  (void)g;
}

}  // namespace internal
}  // namespace ceres
```