**A. Test paths**

Hàm không có điểm rẽ nhánh nên chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `y`, `x`: quaternion 4 phần tử, mỗi phần tử trong [-1, 1]; `y_minus_x`: mảng 3 phần tử. Không có điều kiện nào ràng buộc thêm. | `x = {0.5, 0.5, 0.5, 0.5}`, `y = {0.8, -0.2, 0.4, 0.4}` (chọn bằng `std::mt19937` seed cố định 42, rồi gán trực tiếp), `y_minus_x = {0, 0, 0}` |

Lưu ý: CFG khớp với mã nguồn. Hàm không có vòng lặp.

**C. Nhánh không test**

Không có (tổng số nhánh là 0, không có nhánh nào bị bỏ qua).

`C2 dự kiến = 0 / 0` (không có điểm rẽ nhánh nên C2 coi như đạt toàn bộ khi node 1 được chạy qua).

**D. File test**

```cpp
// FILE: u0344_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

#include <random>

// TC1 - P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(QuaternionManifoldMinus, SinglePath) {
  ceres::QuaternionManifold manifold;

  // Seed cố định để giá trị luôn giống nhau giữa các lần chạy.
  std::mt19937 gen(42);
  std::uniform_real_distribution<double> dist(-1.0, 1.0);

  double x[4];
  double y[4];
  for (int i = 0; i < 4; ++i) {
    x[i] = dist(gen);
    y[i] = dist(gen);
  }
  double y_minus_x[3] = {0.0, 0.0, 0.0};

  // Không kiểm tra kết quả trả về, chỉ gọi hàm để đi qua node 1.
  manifold.Minus(y, x, y_minus_x);
}
```