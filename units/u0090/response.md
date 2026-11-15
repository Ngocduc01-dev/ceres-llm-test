**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào |

CFG khớp với mã nguồn. Macro `CERES_DEFINE_JET_COMPARISON_OPERATOR(<)` sinh ra hàm chỉ có một câu lệnh `return AsScalar(f) < AsScalar(g);`, không có `if`, vòng lặp, `switch` hay `?:`.

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f`, `g` là `Jet<double, 2>` với phần thực là số thực bất kỳ trong [-10, 10] | `f = 3.7`, `g = 6.2` (cố định, không dùng sinh số ngẫu nhiên) |

**C. Nhánh không test**

Không có nhánh nào bị bỏ qua. Hàm không có điểm rẽ nhánh nên tổng số nhánh là 0 và không có vòng lặp cần test.

C2 dự kiến = 0 / 0 (không có nhánh nào cần phủ, đường đi duy nhất P1 được chạy qua nên coi như đạt 100%; dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0090_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetOperatorLessTest, P1_JetLessJet) {
  const Jet<double, 2> f(3.7, 0);
  const Jet<double, 2> g(6.2, 1);
  const bool result = f < g;
  (void)result;  // Không kiểm tra kết quả trả về.
}

}  // namespace internal
}  // namespace ceres
```