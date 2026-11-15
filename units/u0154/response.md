**A. Test paths**

CFG: `START → 1 → END`
- Node 1: `return ceres::Jet<T, N>(std::numeric_limits<T>::round_error());`
- Hàm không có điểm rẽ nhánh nào (tổng số nhánh = 0) và không có vòng lặp.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có tham số đầu vào. Chỉ cần chọn kiểu template `T`, `N` hợp lệ. | `T = double`, `N = 2` |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh nên không có nhánh nào cần phủ.

`C2 dự kiến = 0 / 0` (không có nhánh nào, coi như đạt 100%; TC1 phủ toàn bộ câu lệnh duy nhất, dự kiến, chưa chạy thật)

**D. File test**

```cpp
// FILE: u0154_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(NumericLimitsJetRoundError, P1_SingleStatement) {
  std::numeric_limits<ceres::Jet<double, 2>> obj;
  auto result = obj.round_error();
  (void)result;
}
```