**A. Test paths**

CFG: `START → 1 → END`
- Node 1: `return ceres::Jet<T, N>(std::numeric_limits<T>::signaling_NaN());`
- Hàm không có điểm rẽ nhánh nào (không có `if`, vòng lặp, `switch` hay `?:`).

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Hàm không có tham số. Chỉ chọn tham số template: `T` là kiểu số thực, `N` ≥ 1 | `T = double`, `N = 2` |

**C. Nhánh không test**

Không có. Hàm không có nhánh nào và cũng không có `CHECK`.

`C2 dự kiến = 0 / 0` (không có nhánh nên coi như đạt 100%; một test P1 phủ toàn bộ câu lệnh duy nhất của hàm).

**D. File test**

```cpp
// FILE: u0157_test.cc
#include <limits>

#include "gtest/gtest.h"
#include "ceres/jet.h"

// Path P1: START -> 1 -> END (hàm không có nhánh)
TEST(JetSignalingNaNTest, P1_ReturnJetFromSignalingNaN) {
  std::numeric_limits<ceres::Jet<double, 2>> obj;
  ceres::Jet<double, 2> result = obj.signaling_NaN();
  (void)result;  // Không kiểm tra kết quả trả về
}
```