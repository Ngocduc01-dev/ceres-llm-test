**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm rẽ nhánh, 0 vòng lặp). CFG chỉ có node 1 nên chỉ có một test path duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh nào (node 1 là đoạn lệnh tuần tự, kết thúc bằng `return true`) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `size` từ 1 đến 5; `x`, `delta` là mảng `double` kích thước `size`, mỗi phần tử từ -10 đến 10 | `size` = 3; `x` = {1.5, -2.0, 4.0}; `delta` = {0.5, 3.0, -1.0} |

**C. Nhánh không test**

Không có nhánh nào (hàm không có điểm rẽ nhánh). Mã nguồn khớp với CFG.

`C2 dự kiến = 0 / 0 (không có nhánh; mọi câu lệnh của node 1 đều được chạy bởi TC1)`

**D. File test**

```cpp
// FILE: u0180_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// Path P1: START -> 1 -> END (không có nhánh rẽ)
TEST(EuclideanManifoldPlus, P1_SequentialPath) {
  const int size = 3;
  ceres::EuclideanManifold<ceres::DYNAMIC> manifold(size);

  const double x[size] = {1.5, -2.0, 4.0};
  const double delta[size] = {0.5, 3.0, -1.0};
  double x_plus_delta[size] = {0.0, 0.0, 0.0};

  manifold.Plus(x, delta, x_plus_delta);
}
```