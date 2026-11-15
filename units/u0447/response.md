**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → END | node 1: đúng |
| P2 | START → 1 → 3 → END | node 1: sai |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `num_outputs` ∈ [1, 2]; `jacobians[0] != nullptr` (trỏ tới mảng ≥ `num_outputs*2` double); `jacobians[1]` tùy ý (chọn `nullptr`) | `num_outputs = 2`, `jacobians[0]` = mảng 4 double, `jacobians[1] = nullptr` |
| TC2 | P2 | `num_outputs` ∈ [1, 2]; `jacobians[0] == nullptr`; `jacobians[1]` tùy ý (chọn `nullptr`) | `num_outputs = 1`, `jacobians[0] = nullptr`, `jacobians[1] = nullptr` |

**C. Nhánh không test**

- Không có. Cả hai nhánh của node 1 đều đi tới được.
- Hàm không có vòng lặp, nên không cần xét số lần lặp.
- Lời gọi đệ quy ở node 3 chứa điểm rẽ nhánh `jacobians[1]` của instance khác (`Take1stOrderParts<integer_sequence<int, 2>, 1, 2>`). Điểm này nằm ngoài CFG của unit nên không tính vào tổng số nhánh.
- Giả định: `autodiff.h` đã kéo theo `ceres/jet.h` (cần cho `Jet`). Nếu không, file test sẽ không biên dịch. Không thêm `#include` vì mục 3.3 giới hạn các dòng được dùng.
- `jacobians[0]` ở TC1 có 4 phần tử, vì `num_outputs * N = 2 * 2`; giá trị nhỏ nhất làm được là 2 phần tử (`num_outputs = 1`).

C2 dự kiến = 2 / 2

**D. File test**

```cpp
// FILE: u0447_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/autodiff.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> 2 -> 3 -> END (node 1: đúng)
TEST(Take1stOrderPartsApplyTest, JacobianNonNullTakesPart) {
  using JetT = ceres::Jet<double, 4>;
  Take1stOrderParts<std::integer_sequence<int, 2, 2>> obj;

  const int num_outputs = 2;
  JetT output[2];
  output[0].v[0] = 1.0;
  output[0].v[1] = 2.0;
  output[1].v[0] = 3.0;
  output[1].v[1] = 4.0;

  double jacobian0[4] = {0.0, 0.0, 0.0, 0.0};
  double* jacobians[2] = {jacobian0, nullptr};

  obj.Apply(num_outputs, output, jacobians);
}

// P2: START -> 1 -> 3 -> END (node 1: sai)
TEST(Take1stOrderPartsApplyTest, JacobianNullSkipsPart) {
  using JetT = ceres::Jet<double, 4>;
  Take1stOrderParts<std::integer_sequence<int, 2, 2>> obj;

  const int num_outputs = 1;
  JetT output[1];
  output[0].v[0] = 1.0;
  output[0].v[1] = 2.0;

  double* jacobians[2] = {nullptr, nullptr};

  obj.Apply(num_outputs, output, jacobians);
}

}  // namespace internal
}  // namespace ceres
```