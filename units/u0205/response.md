**Ghi chú:** Mã nguồn ở 3.1 chỉ là hàm bọc, gọi sang overload nhận `ColumnMajorAdapter3x3` và không có rẽ nhánh. CFG ở 3.2 là CFG của overload bên trong. Tôi phủ nhánh theo CFG đó và gọi unit qua `RotationMatrixToQuaternion(const T*, T*)`. `R(i, j)` tương ứng `R[i + 3*j]`, nên các phần tử đường chéo là `R[0]`, `R[4]`, `R[8]`.

**A. Test paths**

Có 3 điểm rẽ nhánh (node 2, 5, 7), tổng 6 nhánh. Không có vòng lặp.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → END | node 2: đúng |
| P2 | START → 1 → 2 → 4 → 5 → 7 → 9 → END | node 2: sai, node 5: sai, node 7: sai |
| P3 | START → 1 → 2 → 4 → 5 → 6 → 7 → 8 → 9 → END | node 2: sai, node 5: đúng, node 7: đúng |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | trace = R00+R11+R22 ≥ 0; phần tử ngoài đường chéo trong [-0.3, 0.3] | đường chéo (0.6, 0.5, 0.4), trace = 1.5 |
| TC2 | P2 | trace < 0, R11 ≤ R00, R22 ≤ R00 | đường chéo (-0.2, -0.5, -0.6), trace = -1.3 |
| TC3 | P3 | trace < 0, R11 > R00, R22 > R(1,1) (khi đó i=1) | đường chéo (-0.8, -0.5, -0.3), trace = -1.6 |

**C. Nhánh không test**

Không có nhánh nào không đi tới được và không có `CHECK`.

C2 dự kiến = 6 / 6

**D. File test**

```cpp
// FILE: u0205_test.cc
#include "gtest/gtest.h"
#include "ceres/rotation.h"

// P1: node 2: đúng
TEST(RotationMatrixToQuaternionTest, TraceNonNegative) {
  // Ma trận cột-chính (column-major), đường chéo: 0.6, 0.5, 0.4
  const double R[9] = {0.6, 0.1, -0.2,
                       0.2, 0.5, 0.3,
                       -0.1, 0.0, 0.4};
  double q[4];
  ceres::RotationMatrixToQuaternion(R, q);
}

// P2: node 2: sai, node 5: sai, node 7: sai
TEST(RotationMatrixToQuaternionTest, NegativeTraceFirstDiagonalLargest) {
  // Đường chéo: -0.2, -0.5, -0.6
  const double R[9] = {-0.2, 0.1, -0.1,
                       0.2, -0.5, 0.3,
                       0.1, -0.3, -0.6};
  double q[4];
  ceres::RotationMatrixToQuaternion(R, q);
}

// P3: node 2: sai, node 5: đúng, node 7: đúng
TEST(RotationMatrixToQuaternionTest, NegativeTraceThirdDiagonalLargest) {
  // Đường chéo: -0.8, -0.5, -0.3
  const double R[9] = {-0.8, 0.2, 0.1,
                       -0.1, -0.5, 0.3,
                       0.2, -0.2, -0.3};
  double q[4];
  ceres::RotationMatrixToQuaternion(R, q);
}
```