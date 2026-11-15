**A. Test paths**

Unit không có điểm rẽ nhánh nào (CFG chỉ có node 1), nên chỉ có một test path. CFG khớp với mã nguồn: dòng 498 chuyển tiếp sang bản overload nhận `RowMajorAdapter3x3(R)`.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh nào (0 điểm rẽ nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `euler[0..2]` ∈ [-1.0, 1.0] (radian); `R[0..8]` là mảng đầu ra, khởi tạo 0 | 3 giá trị sinh bằng `std::mt19937` seed cố định 42, `uniform_real_distribution<double>(-1.0, 1.0)` |

**C. Nhánh không test**

Không có. Unit không có điểm rẽ nhánh và không có `CHECK`.

`C2 dự kiến = 0 / 0` (không có nhánh nào, coi như đạt 100% sau khi node 1 được chạy qua bởi TC1).

**D. File test**

```cpp
// FILE: u0208_test.cc
#include <random>

#include "ceres/rotation.h"
#include "gtest/gtest.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(EulerAnglesToRotationRowMajorTest, TC1_P1_YOddTaitBryanIntrinsic) {
  using System = ceres::internal::EulerSystem<ceres::internal::axis::Y,
                                              ceres::internal::Odd,
                                              ceres::internal::TaitBryan,
                                              ceres::internal::Intrinsic>;

  std::mt19937 gen(42);
  std::uniform_real_distribution<double> dist(-1.0, 1.0);

  double euler[3];
  for (int i = 0; i < 3; ++i) {
    euler[i] = dist(gen);
  }
  double R[9] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

  EulerAnglesToRotation<System>(euler, R);
}

}  // namespace internal
}  // namespace ceres
```