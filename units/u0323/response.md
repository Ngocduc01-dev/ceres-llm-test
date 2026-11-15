**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm rẽ nhánh, 0 nhánh, không có vòng lặp, không có `CHECK`). CFG khớp với mã nguồn. Chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh (đường thẳng, node 1: `return radius_`) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `options.initial_radius` là số thực dương bất kỳ (ví dụ 1e-3 đến 1e6). Hàm `Radius()` không có tham số. | `initial_radius = 5000.0` (cố định, không dùng số ngẫu nhiên) |

**C. Nhánh không test**

Không có nhánh nào bị bỏ qua (hàm không có điểm rẽ nhánh, không có `CHECK`).

`C2 dự kiến = 0 / 0` (không có nhánh; đường duy nhất P1 được phủ hoàn toàn, tương đương 100%)

**D. File test**

```cpp
// FILE: u0323_test.cc
#include "gtest/gtest.h"
#include "ceres/levenberg_marquardt_strategy.h"

// P1: START -> 1 -> END (không có nhánh rẽ)
TEST(LevenbergMarquardtStrategyRadiusTest, TC1_ReturnRadius) {
  ceres::internal::TrustRegionStrategy::Options options;
  options.initial_radius = 5000.0;
  ceres::internal::LevenbergMarquardtStrategy strategy(options);
  double r = strategy.Radius();
  (void)r;  // Không kiểm tra kết quả trả về
}
```