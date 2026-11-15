**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f.a` là số thực bất kỳ (double), `f.v` là vector 2 phần tử bất kỳ (không có điều kiện ràng buộc) | `f.a = 2.37`, `f.v = (0.5, -1.25)` |

**C. Nhánh không test**

Không có nhánh nào (hàm không có điểm rẽ nhánh, không có vòng lặp, không có `CHECK`). CFG khớp với mã nguồn.

`C2 dự kiến = 0 / 0` (không có nhánh; hàm chỉ có một đường đi duy nhất nên được coi là phủ đầy đủ 100% khi TC1 chạy qua).

**D. File test**

```cpp
// FILE: u0117_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// Path P1: START -> END (không có điểm rẽ nhánh)
TEST(JetCeilTest, P1_StraightLine) {
  Jet<double, 2> f;
  f.a = 2.37;
  f.v[0] = 0.5;
  f.v[1] = -1.25;

  Jet<double, 2> r = ceil(f);
  (void)r;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
```