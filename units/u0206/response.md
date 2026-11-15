**A. Test paths**

Hàm có 0 điểm rẽ nhánh nên chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `R`: ma trận xoay 3x3 lưu theo cột (9 phần tử, không có điều kiện ràng buộc). Chọn xoay quanh trục z một góc θ ∈ (0, π/2). `angle_axis`: mảng 3 phần tử. | θ = 0.3, `R = {cos θ, sin θ, 0, −sin θ, cos θ, 0, 0, 0, 1}`; `angle_axis = {0, 0, 0}` |

Ma trận 3x3 cần 9 phần tử nên vượt giới hạn 5 phần tử. Đây là kích thước bắt buộc của đầu vào.

**C. Nhánh không test**

Không có nhánh nào, vì hàm không có điểm rẽ nhánh và không có `CHECK`.

`C2 dự kiến = 0 / 0` (tổng số nhánh bằng 0, nên coi như phủ đủ; dự kiến, chưa chạy thật).

Mã nguồn khớp với CFG.

**D. File test**

```cpp
// FILE: u0206_test.cc
#include <cmath>

#include "ceres/rotation.h"
#include "gtest/gtest.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(RotationMatrixToAngleAxisColumnMajorTest, SinglePath) {
  const double theta = 0.3;  // giá trị cố định trong (0, pi/2)
  const double c = std::cos(theta);
  const double s = std::sin(theta);

  // Ma trận xoay quanh trục z, lưu theo cột (column-major).
  const double R[9] = {c, s, 0.0, -s, c, 0.0, 0.0, 0.0, 1.0};
  double angle_axis[3] = {0.0, 0.0, 0.0};

  // Không kiểm tra kết quả trả về, chỉ gọi hàm một lần.
  RotationMatrixToAngleAxis<double>(R, angle_axis);
}

}  // namespace internal
}  // namespace ceres
```