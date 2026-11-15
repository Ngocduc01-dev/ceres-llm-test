**A. Test paths**

Hàm không có điểm rẽ nhánh (0 điểm rẽ nhánh, 0 nhánh). Chỉ có một đường đi duy nhất. Mã nguồn khớp với CFG (node 1 là biểu thức `return`, gồm các phép `operator*`).

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh (không có điểm rẽ nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | y, v: vector 4×1 kiểu double, mỗi phần tử trong [-5, 5]; beta: double trong [-5, 5] (không có điều kiện đường đi ràng buộc) | y, v, beta sinh bằng `std::mt19937` seed cố định 42 (giá trị ngẫu nhiên trong khoảng trên) |

**C. Nhánh không test**

Không có nhánh nào (hàm không có điểm rẽ nhánh, không có vòng lặp, không có `CHECK`).
`C2 dự kiến = 0 / 0` (không có nhánh nào; mọi câu lệnh của hàm đều được chạy bởi TC1, tức phủ 100% câu lệnh).

**D. File test**

```cpp
// FILE: u0056_test.cc
#include <random>

#include "Eigen/Core"
#include "ceres/internal/householder_vector.h"
#include "gtest/gtest.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ApplyHouseholderVectorTest, P1_SingleStraightPath) {
  std::mt19937 gen(42);
  std::uniform_real_distribution<double> dist(-5.0, 5.0);

  Eigen::Matrix<double, 4, 1> y;
  Eigen::Matrix<double, 4, 1> v;
  for (int i = 0; i < 4; ++i) {
    y(i) = dist(gen);
    v(i) = dist(gen);
  }
  const double beta = dist(gen);

  Eigen::Matrix<double, 4, 1> result =
      ApplyHouseholderVector(y, v, beta);
  (void)result;  // Không kiểm tra kết quả trả về.
}

}  // namespace internal
}  // namespace ceres
```