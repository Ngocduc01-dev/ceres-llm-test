**A. Test paths**

Hàm không có điểm rẽ nhánh (0 điểm rẽ nhánh). CFG chỉ có một node 1 (`operator*`), nên chỉ có một test path.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh nào (không có điểm rẽ nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f.a` là số thực bất kỳ (không có điều kiện đường đi); `f.v` là vector 2 phần tử bất kỳ | `f.a = -3.0`, `f.v = (1.5, -2.0)` |

**C. Nhánh không test**

Không có nhánh nào cần loại trừ; không có điểm rẽ nhánh và không có `CHECK`. Mã nguồn khớp với CFG (`abs`, `copysign` và `operator*` đều không rẽ nhánh theo cú pháp của hàm này).

`C2 dự kiến = 0 / 0` (không có nhánh nào; hàm được coi là phủ hoàn toàn khi node 1 được chạy qua, tức 100%).

**D. File test**

```cpp
// FILE: u0100_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetAbsTest, TC1_P1_NoBranch) {
  Jet<double, 2> f;
  f.a = -3.0;
  f.v[0] = 1.5;
  f.v[1] = -2.0;

  Jet<double, 2> r = abs(f);
  (void)r;
}

}  // namespace internal
}  // namespace ceres
```