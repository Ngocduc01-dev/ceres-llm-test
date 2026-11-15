**A. Test paths**

Hàm có 0 điểm rẽ nhánh, nên chỉ có một đường đi. CFG khớp với mã nguồn.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh. Chạy tuần tự qua node 1 (gọi overload với `IsDynamic()` = false và `ParameterBlockIndices()` = `0, 1`). |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `ParameterDims<false, 2, 2>` (2 khối tham số, mỗi khối 2 phần tử). `x`, `y`: mỗi mảng 2 số `double` trong [-5, 5]. `output`: 1 phần tử. Không có điều kiện ràng buộc vì không có nhánh. | `x = {1.5, -2.0}`, `y = {3.0, 0.5}`, `output = {0.0}` |

**C. Nhánh không test**

Không có nhánh nào bị bỏ qua, vì hàm không có điểm rẽ nhánh nên không có nhánh `CHECK`.

`C2 dự kiến = 0 / 0` (không có nhánh nào, nên coi là 100% phủ). Đây là giá trị dự kiến, chưa chạy thật.

**D. File test**

```cpp
// FILE: u0065_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/variadic_evaluate.h"

namespace ceres {
namespace internal {

namespace {

// Functor 2 khối tham số (mỗi khối 2 phần tử), 1 residual.
struct BinaryScalarCost {
  bool operator()(const double* x, const double* y, double* out) const {
    out[0] = x[0] * y[0] + x[1] * y[1];
    return true;
  }
};

}  // namespace

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(VariadicEvaluateImplTest, TC1_StaticTwoBlocks) {
  BinaryScalarCost functor;
  const double x[2] = {1.5, -2.0};
  const double y[2] = {3.0, 0.5};
  const double* const input[2] = {x, y};
  double output[1] = {0.0};

  // Không kiểm tra kết quả trả về.
  VariadicEvaluateImpl<ParameterDims<false, 2, 2>>(
      functor, input, output, nullptr);
}

}  // namespace internal
}  // namespace ceres
```