**A. Test paths**

CFG: `START → 1 → END`. Node 1 là `return ceres::Jet<T, N>((std::numeric_limits<T>::min)());`. Hàm không có điểm rẽ nhánh nào (không có `if`, vòng lặp, `switch` hay `?:`), nên chỉ có một đường đi.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh (không có điểm rẽ nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Hàm không nhận tham số. Chỉ cần chọn kiểu template: `T` là kiểu số thực, `N` > 0. | `T = double`, `N = 2` |

**C. Nhánh không test**

Không có nhánh nào bị bỏ qua. Hàm không có điểm rẽ nhánh nên tổng số nhánh bằng 0.

`C2 dự kiến = 0 / 0` (không có nhánh nào để phủ; đường đi duy nhất P1 được chạy hết bởi TC1).

**D. File test**

```cpp
// FILE: u0151_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// Path P1: START -> 1 -> END (hàm không có điểm rẽ nhánh)
TEST(NumericLimitsJetMin, P1_ReturnJetFromMin) {
  std::numeric_limits<ceres::Jet<double, 2>> obj;
  ceres::Jet<double, 2> result = (obj.min)();
  (void)result;  // Không kiểm tra kết quả trả về
}
```