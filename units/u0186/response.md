**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào (chỉ có node 1: `return 3`) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có tham số đầu vào. Chỉ cần một object `QuaternionManifold` được tạo bằng constructor mặc định. | Không áp dụng (không có giá trị ngẫu nhiên, không cần seed) |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh và không có vòng lặp. Không có `CHECK`.

C2 dự kiến = 0 / 0 (tổng số nhánh là 0, nên mọi nhánh đều được phủ; đường đi duy nhất P1 được chạy qua; dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0186_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(QuaternionManifoldTangentSize, TC1_ReturnThree) {
  ceres::QuaternionManifold manifold;
  int tangent_size = manifold.TangentSize();
  (void)tangent_size;  // Không kiểm tra kết quả trả về.
}
```