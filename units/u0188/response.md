**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh (0 điểm rẽ nhánh); node 1: `return 3` |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có đầu vào (hàm không tham số; object tạo bằng constructor mặc định `EigenQuaternionManifold()`) | Không có |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh nên không có nhánh nào cần loại trừ; không có vòng lặp và không có `CHECK`.
Ghi chú: CFG khớp với mã nguồn (dòng 393 chỉ có `return 3`).
`C2 dự kiến = 0 / 0` (tổng số nhánh bằng 0, độ phủ nhánh được coi là đạt đầy đủ khi node 1 được thực thi; TC1 phủ toàn bộ đường đi START → 1 → END).

**D. File test**

```cpp
// FILE: u0188_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(EigenQuaternionManifoldTangentSize, P1_ReturnsConstant) {
  ceres::EigenQuaternionManifold manifold;
  manifold.TangentSize();
}
```