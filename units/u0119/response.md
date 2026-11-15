**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh (0 điểm rẽ nhánh), đi thẳng qua node 1 |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f.a` là số thực bất kỳ (không có điều kiện đường đi); `f.v` là vector 2 phần tử, mỗi phần tử số thực bất kỳ | `f.a = 1.5`, `f.v = (0.5, -2.0)` (cố định, chọn trong khoảng [-5, 5]) |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh nên tổng số nhánh là 0 và không có vòng lặp.
`C2 dự kiến = 0 / 0` (không có nhánh nào; mọi câu lệnh ở node 1 đều được chạy bởi TC1, tức phủ 100% câu lệnh).

**D. File test**

```cpp
// FILE: u0119_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetExp2, P1_NoBranch) {
  Jet<double, 2> f;
  f.a = 1.5;
  f.v[0] = 0.5;
  f.v[1] = -2.0;
  Jet<double, 2> r = exp2(f);
  (void)r;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
```