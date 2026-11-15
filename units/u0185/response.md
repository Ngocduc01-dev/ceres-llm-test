**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh; đi thẳng qua node 1 (`return 4`) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có tham số đầu vào; chỉ cần một object `QuaternionManifold` được tạo bằng constructor mặc định | Không có (object mặc định) |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh nên không có nhánh nào cần phủ và không có vòng lặp hay `CHECK`. Một test là đủ để đi hết đường duy nhất.

C2 dự kiến = 0 / 0 (tổng số nhánh = 0, nên mọi câu lệnh đều được phủ bởi P1 và độ phủ coi như đạt 100%).

**D. File test**

```cpp
// FILE: u0185_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(QuaternionManifoldAmbientSize, P1_ReturnsConstant) {
  ceres::QuaternionManifold manifold;
  manifold.AmbientSize();
}
```