**A. Test paths**

Hàm không có điểm rẽ nhánh (0 điểm rẽ nhánh, 0 nhánh, không có vòng lặp, không có `CHECK`). CFG khớp với mã nguồn.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh nào (đường đi duy nhất) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có tham số đầu vào của hàm. Object tạo từ `TrustRegionStrategy::Options` mặc định (không có điều kiện ràng buộc). | Options mặc định, không đặt giá trị nào |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh nên tổng số nhánh là 0; mọi câu lệnh (node 1) đều được chạy bởi TC1.

`C2 dự kiến = 0 / 0` (không có nhánh nào; node 1 được phủ 100% câu lệnh, dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0282_test.cc
#include "gtest/gtest.h"
#include "ceres/dogleg_strategy.h"

namespace ceres {
namespace internal {

// TC1 - P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(DoglegStrategyStepIsInvalidTest, P1_TC1_StraightLine) {
  TrustRegionStrategy::Options options;
  DoglegStrategy strategy(options);
  strategy.StepIsInvalid();
}

}  // namespace internal
}  // namespace ceres
```