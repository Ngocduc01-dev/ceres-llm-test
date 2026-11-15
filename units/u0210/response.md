**A. Test paths**

Hàm không có điểm rẽ nhánh (0 điểm rẽ nhánh, 0 nhánh). Chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

Ghi chú: CFG khớp mã nguồn. Node 1 gọi overload hai tham số `EulerAnglesToRotationMatrix(euler, RowMajorAdapter3x3(R))`. Tham số `row_stride_parameter` không được dùng.

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `euler[3]` (độ): mỗi phần tử trong [-180, 180]; `row_stride_parameter` = 3 (stride của ma trận 3x3 row-major); `R[9]` khởi tạo 0 | Sinh bằng `std::mt19937` seed cố định 12345, `uniform_real_distribution<double>(-180, 180)` |

**C. Nhánh không test**

Không có nhánh nào (hàm không có điểm rẽ nhánh, không có `CHECK`).

`C2 dự kiến = 0 / 0` (không có nhánh; toàn bộ câu lệnh node 1 được thực thi, tương đương 100%).

**D. File test**

```cpp
// FILE: u0210_test.cc
#include <random>

#include "ceres/rotation.h"
#include "gtest/gtest.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(EulerAnglesToRotationMatrixRowStride, SinglePath) {
  std::mt19937 gen(12345);
  std::uniform_real_distribution<double> dist(-180.0, 180.0);

  double euler[3];
  for (int i = 0; i < 3; ++i) {
    euler[i] = dist(gen);
  }
  double R[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

  ceres::EulerAnglesToRotationMatrix<double>(euler, 3, R);
}
```