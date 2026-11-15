**CFG:** START → 1 (`return x[0]*y[0] + x[1]*y[1] + x[2]*y[2]`) → END

Điểm rẽ nhánh: 0 → tổng số nhánh = 0.

**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | x[0..2], y[0..2] là số thực bất kỳ (ví dụ −10 đến 10), không có ràng buộc | x = {1.5, -2.0, 3.25}, y = {0.5, 4.0, -1.0} (cố định, không dùng sinh số ngẫu nhiên) |

**C. Nhánh không test:** không có (hàm không có điểm rẽ nhánh, không có vòng lặp, không có `CHECK`).
`C2 dự kiến = 0 / 0` (không có nhánh; mọi câu lệnh đều được chạy bởi TC1, tức phủ 100% câu lệnh).

**D. File test**

```cpp
// FILE: u0213_test.cc
#include "gtest/gtest.h"
#include "ceres/rotation.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(DotProductTest, P1_StraightLine) {
  const double x[3] = {1.5, -2.0, 3.25};
  const double y[3] = {0.5, 4.0, -1.0};
  double result = ceres::DotProduct<double>(x, y);
  (void)result;  // Không kiểm tra kết quả trả về
}
```