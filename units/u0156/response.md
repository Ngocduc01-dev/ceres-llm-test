**CFG của unit** `quiet_NaN()`

- START → node 1: `return ceres::Jet<T, N>(std::numeric_limits<T>::quiet_NaN());` → END
- Không có điểm rẽ nhánh (không có if/for/while/switch/?:). Tổng số nhánh = 0.

**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh (đường đi tuyến tính duy nhất) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có tham số đầu vào; chọn kiểu template T = double, N = 2 | `Jet<double, 2>` |

**C. Nhánh không test**

Không có nhánh nào (hàm không có điểm rẽ nhánh, không có `CHECK`).
`C2 dự kiến = 0 / 0` (không có nhánh; hàm chỉ cần được chạy 1 lần là phủ toàn bộ câu lệnh).

**D. File test**

```cpp
// FILE: u0156_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

#include <limits>

// Path P1: START -> 1 -> END (không có nhánh rẽ)
TEST(NumericLimitsJetQuietNaN, P1_LinearPath) {
  std::numeric_limits<ceres::Jet<double, 2>> obj;
  ceres::Jet<double, 2> result = obj.quiet_NaN();
  (void)result;  // Không kiểm tra kết quả trả về
}
```