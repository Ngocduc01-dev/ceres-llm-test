**A. Test paths**

CFG khớp với mã nguồn. Hàm không có điểm rẽ nhánh nào (0 điểm, 0 nhánh), nên chỉ có một đường đi.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh, không có vòng lặp |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f` và `g` là `Jet<double, 2>` (thoả `CompatibleJetOperands_v`). Phần scalar `f.a`, `g.a` là số thực bất kỳ, chọn trong [-5, 5]. Hai hệ số đạo hàm `v` là số thực bất kỳ. | `f.a = 1.7`, `g.a = -3.2`, `f` có `v[0] = 1`, `g` có `v[1] = 1` |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh nào và không có `CHECK`.

`C2 dự kiến = 0 / 0` (không có nhánh nào cần phủ; test chạy qua node 1 nên đạt C1 100%).

**D. File test**

```cpp
// FILE: u0139_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {

// Path P1: START -> 1 -> END (không có nhánh rẽ)
TEST(IslessgreaterTest, TC1_JetJet_P1) {
  Jet<double, 2> f(1.7, 0);
  Jet<double, 2> g(-3.2, 1);
  bool r = islessgreater(f, g);
  (void)r;  // không kiểm tra kết quả trả về
}

}  // namespace ceres
```