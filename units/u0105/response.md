**A. Test paths**

Hàm không có điểm rẽ nhánh (tổng số nhánh = 0), nên chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f.a` là số thực bất kỳ (ví dụ −5 đến 5); `f.v` là vector 2 phần tử, mỗi phần tử từ −5 đến 5 | `f.a = 1.3`, `f.v = (−2.1, 3.4)` |

**C. Nhánh không test**

Không có nhánh nào bị bỏ qua (hàm không có điểm rẽ nhánh, không có `CHECK`, không có vòng lặp).
`C2 dự kiến = 0 / 0` (không có nhánh nào; mọi câu lệnh đều chạy khi gọi hàm một lần, tức đạt C1 = 100%).

**D. File test**

```cpp
// FILE: u0105_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetExpm1Test, P1_SingleStraightPath) {
  Jet<double, 2> f;
  f.a = 1.3;
  f.v[0] = -2.1;
  f.v[1] = 3.4;

  Jet<double, 2> r = expm1(f);
  (void)r;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
```