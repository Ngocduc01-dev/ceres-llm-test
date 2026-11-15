**A. Test paths**

Hàm không có điểm rẽ nhánh (0 điểm rẽ nhánh, tổng số nhánh = 0). Chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh nào (không có điểm rẽ nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `q[4]` kiểu double, mỗi phần tử bất kỳ (không có điều kiện ràng buộc); `R[9]` là mảng đầu ra | q = {0.5, 0.5, 0.5, 0.5} (quaternion đơn vị, chọn cố định); R = 9 phần tử khởi tạo 0 |

**C. Nhánh không test**

Không có nhánh nào không test (hàm không có điểm rẽ nhánh, không có `CHECK`, không có vòng lặp).
Ghi chú: CFG khớp với mã nguồn. Dòng 703 gọi overload `QuaternionToRotation(q, RowMajorAdapter3x3(R))`; các nhánh bên trong overload đó không thuộc unit này.

`C2 dự kiến = 0 / 0` (không có nhánh nào; unit được phủ toàn bộ câu lệnh node 1 bằng TC1)

**D. File test**

```cpp
// FILE: u0212_test.cc
#include "gtest/gtest.h"
#include "ceres/rotation.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(QuaternionToRotationRowMajor, P1_SinglePath) {
  const double q[4] = {0.5, 0.5, 0.5, 0.5};
  double R[9] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  ceres::QuaternionToRotation<double>(q, R);
}
```