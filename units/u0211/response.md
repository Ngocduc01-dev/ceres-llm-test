**A. Test paths**

Hàm không có điểm rẽ nhánh (0 điểm rẽ nhánh, 0 nhánh). Chỉ có một đường đi duy nhất. Hàm gọi overload khác nhận `RowMajorAdapter3x3(R)`, nên chỉ cần gọi hàm một lần là đi qua node 1.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `q[4]` kiểu double, mỗi phần tử là số thực bất kỳ (không có điều kiện ràng buộc); `R[9]` là mảng đầu ra | `q = {0.5, -0.25, 0.75, 0.125}` (chọn từ [-1, 1], cố định); `R` khởi tạo 0 |

**C. Nhánh không test**

Không có nhánh nào (tổng số nhánh = 0, không có nhánh `CHECK`).
`C2 dự kiến = 0 / 0` (không có điểm rẽ nhánh nên mọi node được phủ bởi 1 test; dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0211_test.cc
#include "gtest/gtest.h"
#include "ceres/rotation.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(QuaternionToScaledRotationTest, TC1_P1_SinglePath) {
  const double q[4] = {0.5, -0.25, 0.75, 0.125};
  double R[3 * 3] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  ceres::QuaternionToScaledRotation<double>(q, R);
}
```