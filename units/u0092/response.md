**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào (hàm chỉ có 1 câu lệnh `return`) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f.a`, `g.a` là số thực double bất kỳ (hữu hạn). Phần đạo hàm `v` không ảnh hưởng, vì phép so sánh chỉ dùng phần vô hướng `a`. | `f = Jet<double, 7>(3.5)`, `g = Jet<double, 7>(-1.25)` (giá trị cố định, không dùng sinh số ngẫu nhiên) |

**C. Nhánh không test**

- Không có. Hàm có 0 điểm rẽ nhánh nên không có nhánh nào cần phủ, và không có `CHECK`.
- Mã nguồn là macro `CERES_DEFINE_JET_COMPARISON_OPERATOR(>)`, sinh ra `operator>` template với kiểu `Lhs`, `Rhs` thoả `PromotableJetOperands_t`. Nội dung hàm là `return AsScalar(f) > AsScalar(g);`, khớp với CFG.
- `C2 dự kiến = 0 / 0` (không có nhánh nào; 1 test đi hết đường START → 1 → END, nên phủ đầy đủ).

**D. File test**

```cpp
// FILE: u0092_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetOperatorGreaterTest, TC1_ScalarComparisonPath) {
  const Jet<double, 7> f(3.5);
  const Jet<double, 7> g(-1.25);
  [[maybe_unused]] const bool result = f > g;
}

}  // namespace ceres
```