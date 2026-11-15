**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm rẽ nhánh, 0 nhánh). Không có vòng lặp. Chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | n: số nguyên bất kỳ (chọn 0 ≤ n ≤ 5); x: số thực bất kỳ (chọn 0.5 ≤ x ≤ 5.0) | n = 3, x = 2.7 |

**C. Nhánh không test**

Không có. Hàm không chứa điểm rẽ nhánh, `CHECK` hay vòng lặp. Mã nguồn khớp với CFG.

C2 dự kiến = 0 / 0 (không có nhánh nào; mọi câu lệnh đã được phủ bởi TC1).

**D. File test**

```cpp
// FILE: u0128_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(BesselJnTest, SinglePath) {
  const int n = 3;
  const double x = 2.7;
  double result = ceres::BesselJn(n, x);
  (void)result;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
```