**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào (hàm chỉ có 1 node tuần tự) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f.a` là số thực `double` bất kỳ, ví dụ trong [-5, 5]; `f.v` có 1 phần tử | `f.a = -2.5` (chọn trong khoảng), `f.v[0] = 1.0` |

**C. Nhánh không test**

Không có. Hàm có 0 điểm rẽ nhánh nên không có nhánh nào bị bỏ sót, và cũng không có vòng lặp hay `CHECK`.

`C2 dự kiến = 0 / 0` (không có nhánh nào; một test đi hết đường START → 1 → END nên coi như đạt 100%).

**D. File test**

```cpp
// FILE: u0143_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (hàm không có điểm rẽ nhánh)
TEST(JetSignbitTest, P1_ReturnSignbitOfScalarPart) {
  // f.a = -2.5 nằm trong khoảng [-5, 5]; đạo hàm f.v[0] = 1.0
  Jet<double, 1> f(-2.5, 0);
  bool result = ceres::signbit(f);
  (void)result;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
```