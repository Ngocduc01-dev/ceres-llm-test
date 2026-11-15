**A. Test paths**

Hàm có 0 điểm rẽ nhánh nên chỉ có 1 đường đi duy nhất. CFG khớp với mã nguồn.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f`, `g` là `Jet<double, 1>` bất kỳ (phần thực là số double bất kỳ, không có điều kiện đường đi) | `f` = 1.5, `g` = -2.25 (cố định, không dùng số ngẫu nhiên) |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh và không có `CHECK`.

`C2 dự kiến = 0 / 0` (tổng số nhánh bằng 0, nên mọi đường đi đều được phủ; dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0141_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(IsUnorderedJetTest, P1_JetJet) {
  const Jet<double, 1> f(1.5);
  const Jet<double, 1> g(-2.25);
  [[maybe_unused]] const bool result = ceres::isunordered(f, g);
}

}  // namespace
}  // namespace ceres
```