**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm rẽ nhánh, 0 nhánh). Chỉ có một đường đi duy nhất. CFG khớp với mã nguồn (dòng 619 `return` nằm cùng node 1 khi đi tới END).

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | f.a ∈ (−1, 1) để `sqrt` hợp lệ; f.v là vector 2 phần tử, mỗi phần tử ∈ [−5, 5] | f.a = 0.37; f.v = (1.5, −2.0) |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh nên không có nhánh nào bị bỏ, không có vòng lặp và không có `CHECK`.

`C2 dự kiến = 0 / 0` (không có nhánh; một test chạy toàn bộ hàm, nên coi như đạt 100%).

**D. File test**

```cpp
// FILE: u0108_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetAcosTest, P1_SingleStraightPath) {
  Jet<double, 2> f;
  f.a = 0.37;
  f.v[0] = 1.5;
  f.v[1] = -2.0;

  Jet<double, 2> r = acos(f);
  (void)r;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
```