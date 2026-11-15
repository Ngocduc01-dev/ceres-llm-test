**A. Test paths**

Hàm không có điểm rẽ nhánh (0 điểm rẽ nhánh, 0 nhánh). CFG khớp với mã nguồn. Chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh (node 1 là câu lệnh `return fpclassify(f.a)`) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f.a` là `double` bất kỳ (không có điều kiện ràng buộc); `f.v` là vector 12 phần tử bất kỳ | `f.a = 3.5`; `f.v` = 0 (mặc định) |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh và không có vòng lặp, nên không có nhánh nào bị bỏ.

C2 dự kiến = 0 / 0 (không có nhánh; đường đi duy nhất P1 được chạy qua nên toàn bộ câu lệnh được phủ, tương đương 100%).

**D. File test**

```cpp
// FILE: u0142_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetFpclassifyTest, SinglePath) {
  Jet<double, 12> f;
  f.a = 3.5;
  (void)fpclassify(f);
}

}  // namespace internal
}  // namespace ceres
```