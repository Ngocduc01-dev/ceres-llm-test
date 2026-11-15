**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh; chỉ có node 1 (`return 4`) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có đầu vào (hàm không tham số; object tạo bằng constructor mặc định) | Không áp dụng |

**C. Nhánh không test:** không có (hàm không có điểm rẽ nhánh, CFG khớp với mã nguồn).
`C2 dự kiến = 0 / 0` (không có nhánh nào; mọi câu lệnh đều được chạy qua bởi P1, tức là C1 = 100%).

**D. File test**

```cpp
// FILE: u0187_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// P1: START -> 1 -> END
TEST(EigenQuaternionManifoldAmbientSize, TC1_ReturnsConstant) {
  ceres::EigenQuaternionManifold manifold;
  manifold.AmbientSize();
}
```