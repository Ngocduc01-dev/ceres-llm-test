**Ghi chú:** CFG đã cho không khớp mã nguồn. Theo mã nguồn (dòng 233–234), `Apply` là hàm **rỗng** của đặc hoá cơ sở `Make1stOrderPerturbations<std::integer_sequence<int>, ParameterIdx, Offset>`. Hàm không có lệnh nào và không có điểm rẽ nhánh. Tôi tin mã nguồn, nên không có node 1 như trong CFG; đường đi chỉ là START → END.

**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Hai tham số không được dùng, nên không có ràng buộc. `parameters`: mảng con trỏ, 1 phần tử. `x`: mảng `Jet<double, 4>` tối đa 5 phần tử. | `parameters = {&p}` với `p = 1.5`; `x[2]` mặc định; `ParameterIdx = 0`, `Offset = 0` |

**C. Nhánh không test:** không có. `C2 dự kiến = 0 / 0` (không có nhánh nào; hàm rỗng nên chỉ cần gọi 1 lần để đi qua START → END).

**D. File test**

```cpp
// FILE: u0024_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/autodiff.h"

namespace ceres {
namespace internal {

// P1: START -> END (hàm rỗng, không có điểm rẽ nhánh)
TEST(Make1stOrderPerturbationsEmptyApply, TC1_StartToEnd) {
  using JetT = Jet<double, 4>;
  Make1stOrderPerturbations<std::integer_sequence<int>, 0, 0> obj;

  double p = 1.5;
  double const* parameters[1] = {&p};
  JetT x[2];

  obj.Apply<double, JetT>(parameters, x);
}

}  // namespace internal
}  // namespace ceres
```