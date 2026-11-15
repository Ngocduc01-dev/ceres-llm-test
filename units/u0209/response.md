**A. Test paths**

Hàm có 0 điểm rẽ nhánh và không có vòng lặp. CFG khớp với mã nguồn: một node duy nhất, gọi hàm quá tải nhận `RowMajorAdapter3x3(R)`. Vì vậy chỉ có một đường đi.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh nào (0 điểm rẽ nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `R`: 9 số double, ma trận quay 3×3 theo hàng (row-major), phần tử trong [-1, 1]. `euler`: mảng 3 double (đầu ra). | Quay quanh trục Z góc 0.7 rad: `R = {0.7648421873, -0.6442176872, 0, 0.6442176872, 0.7648421873, 0, 0, 0, 1}`. `euler = {0, 0, 0}` |

Ghi chú: ma trận 3×3 bắt buộc có 9 phần tử nên vượt giới hạn 5 phần tử. Giá trị là hằng cố định, không dùng số ngẫu nhiên.

**C. Nhánh không test**

Không có nhánh nào bị bỏ. Hàm không có điểm rẽ nhánh và không có `CHECK`.
`C2 dự kiến = 0 / 0` (không có nhánh nào để phủ, nên mọi nhánh đều được phủ; dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0209_test.cc
#include "gtest/gtest.h"
#include "ceres/rotation.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(RotationMatrixToEulerAnglesRowMajorTest, TC1_SinglePath) {
  using System = ceres::internal::EulerSystem<ceres::internal::axis::Z,
                                              ceres::internal::Odd,
                                              ceres::internal::ProperEuler,
                                              ceres::internal::Intrinsic>;
  const double R[9] = {0.7648421873, -0.6442176872, 0.0,
                       0.6442176872, 0.7648421873, 0.0,
                       0.0, 0.0, 1.0};
  double euler[3] = {0.0, 0.0, 0.0};

  ceres::RotationMatrixToEulerAngles<System>(R, euler);
}

}  // namespace internal
}  // namespace ceres
```