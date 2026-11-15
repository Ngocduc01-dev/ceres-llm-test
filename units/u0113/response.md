**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm rẽ nhánh, tổng 0 nhánh). Chỉ có một đường đi duy nhất. Mã nguồn khớp với CFG: dòng 653 là một câu lệnh `return` duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f.a` thuộc double bất kỳ, `f.v` là vector 2 phần tử double; không có điều kiện ràng buộc. Chọn trong [-2, 2] | `f.a` = 0.7; `f.v` = (1.3, -0.4) |

**C. Nhánh không test**

Không có nhánh nào bị bỏ qua (hàm không có điểm rẽ nhánh, không có `CHECK`, không có vòng lặp).

`C2 dự kiến = 0 / 0` (không có nhánh nào; đường P1 duy nhất được chạy qua, tức phủ 100% câu lệnh).

**D. File test**

```cpp
// FILE: u0113_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetSinhTest, TC1_SinhDouble2) {
  Jet<double, 2> f;
  f.a = 0.7;
  f.v[0] = 1.3;
  f.v[1] = -0.4;

  Jet<double, 2> r = sinh(f);
  (void)r;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
```