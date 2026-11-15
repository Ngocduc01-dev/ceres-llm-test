**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh; đi thẳng qua node 1 (`std::copy_n` rồi `return true`) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `size_` (hàm tạo `EuclideanManifold<-1>(size)`): 1..5; `num_rows`: 1..5 sao cho `num_rows * size` ≤ 5 (mảng nhỏ, tối đa 5 phần tử); `x`: con trỏ không dùng đến, mảng 1..5 phần tử; `ambient_matrix`: mảng `num_rows * size` phần tử; `tangent_matrix`: mảng cùng kích thước | `size = 2`, `num_rows = 2` (tích = 4 ≤ 5); `x = {0.3, -0.7}`; `ambient_matrix = {0.5, -1.2, 2.1, 0.9}`; `tangent_matrix = {0, 0, 0, 0}` |

Ghi chú: CFG khớp với mã nguồn. Hàm không có điểm rẽ nhánh nên không cần số ngẫu nhiên; giá trị cố định chọn tay trong khoảng hợp lệ. Hàm không có vòng lặp trong thân (`std::copy_n` là hàm thư viện, không tính).

**C. Nhánh không test**

Không có (hàm có 0 điểm rẽ nhánh, 0 nhánh cần phủ).

`C2 dự kiến = 0 / 0` (không có nhánh nào; đường đi duy nhất P1 được chạy qua, coi như đạt 100%).

**D. File test**

```cpp
// FILE: u0182_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(EuclideanManifoldRightMultiplyByPlusJacobian, TC1_CopyAmbientToTangent) {
  const int size = 2;
  const int num_rows = 2;
  ceres::EuclideanManifold<ceres::DYNAMIC> manifold(size);

  const double x[2] = {0.3, -0.7};
  const double ambient_matrix[4] = {0.5, -1.2, 2.1, 0.9};
  double tangent_matrix[4] = {0.0, 0.0, 0.0, 0.0};

  manifold.RightMultiplyByPlusJacobian(x, num_rows, ambient_matrix,
                                       tangent_matrix);
}
```