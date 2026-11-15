**A. Test paths**

Hàm không có điểm rẽ nhánh nào (không có `if`, vòng lặp, `switch` hay `?:`), nên chỉ có một đường đi duy nhất. Mã nguồn khớp với CFG (node 1 là biểu thức trả về, chứa phép `operator*`).

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f.a` là số thực bất kỳ, chọn trong [0.5, 5]. `f.v` là vector 2 phần tử, tạo bằng `Jet(a, 0)` nên v = (1, 0). | `f.a = 2.3` (chọn cố định, không dùng sinh số ngẫu nhiên) |

**C. Nhánh không test**

- Không có nhánh nào bị bỏ qua, và không có `CHECK`.
- `C2 dự kiến = 0 / 0` (hàm không có nhánh, coi như đạt 100%). Hàm này chỉ cần chạy một lần là phủ toàn bộ.

**D. File test**

```cpp
// FILE: u0130_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(BesselJ1JetTest, P1_StraightLine) {
  Jet<double, 2> f(2.3, 0);
  Jet<double, 2> r = BesselJ1(f);
  (void)r;  // không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
```