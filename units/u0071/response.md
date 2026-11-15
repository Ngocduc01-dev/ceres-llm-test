**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh (0 điểm) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `a`: double bất kỳ (ví dụ −10 đến 10); `v`: biểu thức Eigen (DenseBase) kích thước 4×1 kiểu double, mỗi phần tử trong −10 đến 10 | `a` = 3.5; `v` = `Eigen::Matrix<double,4,1>` với các phần tử {1.5, −2.0, 0.5, 4.0} |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh và không có vòng lặp, nên chỉ có một đường đi duy nhất. Không có `CHECK`.

`C2 dự kiến = 0 / 0` (không có nhánh nào; đường đi duy nhất START → 1 → END được chạy qua, tức 100% câu lệnh).

**D. File test**

```cpp
// FILE: u0071_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetConstructorDenseBaseTest, TC1_ScalarAndDenseVector) {
  using JetType = ceres::Jet<double, 4>;
  Eigen::Matrix<double, 4, 1> v;
  v << 1.5, -2.0, 0.5, 4.0;
  const double a = 3.5;
  JetType j(a, v);
  (void)j;
}
```