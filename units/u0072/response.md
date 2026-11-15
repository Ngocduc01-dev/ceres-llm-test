**A. Test paths**

Hàm không có điểm rẽ nhánh (0 điểm rẽ nhánh), nên chỉ có một test path duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh nào (node 1 là khối lệnh tuần tự: `*this = *this + s; return *this;`) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Object `Jet<double, 2>`: giá trị a và k bất kỳ (k trong [0, 1]); `s` là double bất kỳ (không có điều kiện ràng buộc) | a = 3.5, k = 1, s = 2.25 (chọn cố định, đại diện cho khoảng) |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh và không có vòng lặp hay `CHECK`.

`C2 dự kiến = 0 / 0` (tổng số nhánh = 0, nên C2 được coi là đạt 100% khi test path P1 chạy qua node 1).

**D. File test**

```cpp
// FILE: u0072_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetOperatorPlusEqualScalar, P1_SequentialPath) {
  Jet<double, 2> a(3.5, 1);
  const double s = 2.25;
  a += s;
}

}  // namespace
}  // namespace ceres
```