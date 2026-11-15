**A. Test paths**

CFG: START → 1 → END
- Node 1 (dòng 1334): `return ceres::Jet<T, N>(std::numeric_limits<T>::lowest());`
- Hàm không có điểm rẽ nhánh (không có `if`, vòng lặp, `switch` hay `?:`), nên tổng số nhánh là 0.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có tham số đầu vào. Chỉ chọn kiểu template: `T` là kiểu số thực, `N` ≥ 1. | `T = double`, `N = 2` |

**C. Nhánh không test**

Không có nhánh nào bị bỏ. Hàm không có điểm rẽ nhánh, và không có `CHECK`.

`C2 dự kiến = 0 / 0` (không có nhánh nào cần phủ; TC1 chạy qua toàn bộ câu lệnh duy nhất, nên C1 đạt 100%).

**D. File test**

```cpp
// FILE: u0152_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(NumericLimitsJetLowestTest, TC1_P1_LowestDoubleN2) {
  std::numeric_limits<ceres::Jet<double, 2>> obj;
  ceres::Jet<double, 2> result = obj.lowest();
  (void)result;  // Không kiểm tra kết quả trả về
}
```