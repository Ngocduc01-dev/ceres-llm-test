**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh (0 điểm rẽ nhánh); chỉ đi qua node 1 (các member initializer) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có đầu vào (constructor mặc định không tham số) | Không có |

**C. Nhánh không test**

Không có. Unit không có điểm rẽ nhánh nên không có vòng lặp và không có `CHECK`.
Ghi chú: CFG khớp với mã nguồn (`CRSMatrix() = default;`).
C2 dự kiến = 0 / 0 (tổng số nhánh = 0, không có nhánh nào cần phủ; đường đi duy nhất P1 được chạy qua, tức phủ 100% câu lệnh).

**D. File test**

```cpp
// FILE: u0015_test.cc
#include "gtest/gtest.h"
#include "ceres/crs_matrix.h"

// Path: P1 (START -> 1 -> END), không có điểm rẽ nhánh
TEST(CRSMatrixConstructorTest, DefaultConstructor) {
  ceres::CRSMatrix matrix;
  (void)matrix;
}
```