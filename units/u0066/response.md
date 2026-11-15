**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào (0 nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `input[0]` gồm 2 số thực, mỗi số trong [-5, 5]. `input[1]` gồm 2 số thực, mỗi số trong [-5, 5]. `output` là mảng 2 phần tử, giá trị khởi tạo bất kỳ. Không có điều kiện đường đi, vì hàm không có rẽ nhánh. | `input[0] = {1.5, -0.7}`, `input[1] = {0.3, 2.1}`, `output = {0, 0}` (giá trị cố định, tương đương seed cố định) |

**C. Nhánh không test:** không có. Hàm có 0 điểm rẽ nhánh nên tổng số nhánh là 0, và test TC1 phủ toàn bộ đường đi duy nhất (node 1).
`C2 dự kiến = 0 / 0` (không có nhánh nào cần phủ; coi như đạt 100%, vì node 1 duy nhất được chạy qua).

Ghi chú: `BinaryScalarCost` không có trong các `#include` ở mục 3.3, nên file test tự định nghĩa functor này với `operator()(x, y, residual)`, khớp với `ParameterDims<false, 2, 2>`.

**D. File test**

```cpp
// FILE: u0066_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/variadic_evaluate.h"

namespace ceres {
namespace internal {

// Functor hai khối tham số, mỗi khối có kích thước 2 (khớp ParameterDims<false, 2, 2>).
struct BinaryScalarCost {
  template <typename T>
  bool operator()(const T* x, const T* y, T* residual) const {
    residual[0] = x[0] - y[0];
    residual[1] = x[1] - y[1];
    return true;
  }
};

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(VariadicEvaluateTest, P1_SinglePath) {
  const double x[2] = {1.5, -0.7};
  const double y[2] = {0.3, 2.1};
  const double* const input[2] = {x, y};
  double output[2] = {0.0, 0.0};
  BinaryScalarCost functor;

  VariadicEvaluate<ParameterDims<false, 2, 2>>(functor, input, output);
}

}  // namespace internal
}  // namespace ceres
```