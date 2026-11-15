**Ghi chú về CFG:** CFG ở mục 3.2 là của overload đệ quy (có `if (jacobians[0])`). Mã nguồn dòng 297–300 là overload ở cuối đệ quy, tức là `Take1stOrderParts<std::integer_sequence<int>, ParameterIdx, Total>`, và thân hàm là `{}`. Theo yêu cầu "tin mã nguồn", unit này không có điểm rẽ nhánh nào. Các node 1, 2, 3 của CFG không tồn tại trong unit này.

**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Cả 3 tham số đều không được dùng nên mọi giá trị đều hợp lệ: `int` bất kỳ, `JetT*` bất kỳ (kể cả `nullptr`), `T**` bất kỳ | `int` = 3 (trong khoảng 0–5), `JetT*` trỏ tới mảng `double[2]`, `T**` trỏ tới mảng con trỏ `double*[1]` |

**C. Nhánh không test:** không có. Unit không có điểm rẽ nhánh, nên tổng số nhánh là 0 và không có nhánh nào bị bỏ sót.
`C2 dự kiến = 0 / 0` (không có nhánh nào để phủ; hàm rỗng được chạy qua 1 lần bằng TC1, nên coi là phủ đầy đủ).

**D. File test**

```cpp
// FILE: u0025_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/autodiff.h"

#include <utility>

namespace ceres {
namespace internal {

// Path P1: START -> END (hàm rỗng, không có điểm rẽ nhánh)
TEST(Take1stOrderPartsApplyEmpty, P1_EmptyBodyNoBranch) {
  Take1stOrderParts<std::integer_sequence<int>, 0, 0> obj;

  double outputs[2] = {1.0, 2.0};
  double jac_data[2] = {0.5, 0.25};
  double* jacobians[1] = {jac_data};

  obj.Apply(3, outputs, jacobians);
}

}  // namespace internal
}  // namespace ceres
```