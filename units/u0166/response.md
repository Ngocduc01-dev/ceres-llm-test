**A. Test paths**

Không có điểm rẽ nhánh nào (0 điểm rẽ nhánh, 0 vòng lặp, 0 `CHECK`). Hàm chỉ có một đường đi.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh nào (node 1 là lệnh `return 2 * size_`) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có tham số đầu vào. Object `LineManifold<3>` tạo bằng constructor mặc định. | Không có (không cần sinh số ngẫu nhiên, nên không cần seed) |

**C. Nhánh không test**

Không có. Hàm không có nhánh nào, `CHECK` cũng không có.
C2 dự kiến = 0 / 0 (không có nhánh, đường đi duy nhất P1 được chạy qua nên độ phủ coi như 100%).

**D. File test**

```cpp
// FILE: u0166_test.cc
#include "gtest/gtest.h"
#include "ceres/line_manifold.h"

// P1: START -> 1 -> END (không có nhánh rẽ)
TEST(LineManifoldAmbientSizeTest, TC1_SinglePath) {
  ceres::LineManifold<3> manifold;
  int ambient_size = manifold.AmbientSize();
  (void)ambient_size;  // Không kiểm tra kết quả trả về
}
```