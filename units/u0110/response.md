**A. Test paths**

Hàm không có điểm rẽ nhánh (0 điểm, tổng 0 nhánh). Chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f.a` thuộc (−1, 1) để asin xác định (không có điều kiện đường đi bắt buộc); `f.v` là vector 2 phần tử tuỳ ý | `f.a = 0.37`, `f.v = (0.52, -0.81)` |

**C. Nhánh không test**

Không có nhánh nào bị bỏ (hàm không có điểm rẽ nhánh, không có vòng lặp, không có `CHECK`). Mã nguồn khớp với CFG.

C2 dự kiến = 0 / 0 (không có nhánh nào; mọi câu lệnh được chạy bởi TC1, tức phủ 100% theo quy ước)

**D. File test**

```cpp
// FILE: u0110_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetAsin, SinglePath) {
  Jet<double, 2> f;
  f.a = 0.37;
  f.v[0] = 0.52;
  f.v[1] = -0.81;
  Jet<double, 2> r = asin(f);
  (void)r;
}

}  // namespace internal
}  // namespace ceres
```