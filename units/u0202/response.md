**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào. Chỉ có một đường đi duy nhất. |

CFG khớp với mã nguồn. Node 1 gọi `MinusImpl(...)`, và `MinusImpl` nằm ngoài unit.

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Manifold: `SubsetManifold(3, {true,false,false})` (ambient 3, tangent 2) và `SubsetManifold(2, {false,true})` (ambient 2, tangent 1). Vậy `y` và `x` có 5 phần tử, `y_minus_x` có 3 phần tử. Mỗi phần tử của `y` và `x` nằm trong [-5, 5]. | `y = {1.5, -2.0, 3.0, 0.5, -4.0}`, `x = {1.5, 2.5, -1.0, 0.5, 4.5}`, `y_minus_x = {0, 0, 0}` |

Các giá trị trên được chọn cố định, nên mỗi lần chạy cho cùng kết quả (không dùng hàm sinh số ngẫu nhiên).

**C. Nhánh không test**

Không có nhánh nào. Unit không có điểm rẽ nhánh và không có `CHECK`.

`C2 dự kiến = 0 / 0` (tổng số nhánh bằng 0, nên coi như đạt 100%; dự kiến, chưa chạy thật). Test vẫn thực thi node 1 nên đạt luôn độ phủ câu lệnh.

**D. File test**

```cpp
// FILE: u0202_test.cc
#include "gtest/gtest.h"
#include "ceres/product_manifold.h"

#include <vector>

namespace ceres {
namespace {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ProductManifoldMinusTest, P1_TwoSubsetManifolds) {
  SubsetManifold m1(3, std::vector<bool>{true, false, false});  // ambient 3, tangent 2
  SubsetManifold m2(2, std::vector<bool>{false, true});         // ambient 2, tangent 1
  ProductManifold<SubsetManifold, SubsetManifold> manifold(std::move(m1),
                                                           std::move(m2));

  const double y[5] = {1.5, -2.0, 3.0, 0.5, -4.0};
  const double x[5] = {1.5, 2.5, -1.0, 0.5, 4.5};
  double y_minus_x[3] = {0.0, 0.0, 0.0};

  // Không kiểm tra kết quả trả về.
  manifold.Minus(y, x, y_minus_x);
}

}  // namespace
}  // namespace ceres
```