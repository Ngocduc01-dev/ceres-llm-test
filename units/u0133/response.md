**Ghi chú:** Hàm không có điểm rẽ nhánh nào (CFG khớp mã nguồn). Tổng số nhánh = 0. Chỉ có 1 test path.

**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f.a` là double bất kỳ, `v` (độ dài 1) bất kỳ | `f.a = 3.7`, `f.v[0] = 1.0` (Jet<double, 1>) |

**C. Nhánh không test**

Không có nhánh nào (hàm không có điểm rẽ nhánh). `CHECK` không có trong hàm.

C2 dự kiến = 0 / 0 (không có nhánh; node 1 được chạy bởi TC1, nên đạt phủ toàn bộ câu lệnh).

**D. File test**

```cpp
// FILE: u0133_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetIsInfTest, P1_ReturnIsInfOfScalarPart) {
  Jet<double, 1> f;
  f.a = 3.7;
  f.v[0] = 1.0;
  bool result = isinf(f);
  (void)result;  // không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
```