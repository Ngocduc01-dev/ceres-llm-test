**A. Test paths**

CFG: `START → 1 → END`
- Node 1: `return ceres::Jet<T, N>((std::numeric_limits<T>::max)());`
- Hàm không có điểm rẽ nhánh, không có vòng lặp và không có `CHECK`.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Hàm không có tham số. Kiểu template: `T` là kiểu số thực, `N` ≥ 1. | `T = double`, `N = 2` |

**C. Nhánh không test**

Không có. Tổng số nhánh là 0, nên không có nhánh nào bị bỏ sót.

`C2 dự kiến = 0 / 0` (không có nhánh nào, coi như đạt 100%; dự kiến, chưa chạy thật). Một test đi qua node 1 là đủ để phủ toàn bộ câu lệnh.

**D. File test**

```cpp
// FILE: u0159_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// Path P1: START -> 1 -> END (hàm không có nhánh rẽ)
TEST(NumericLimitsJetMax, P1_ReturnMaxJet) {
  std::numeric_limits<ceres::Jet<double, 2>> obj;
  // Dùng dấu ngoặc để tránh macro max trên Windows.
  ceres::Jet<double, 2> result = (obj.max)();
  (void)result;  // Không kiểm tra kết quả trả về.
}
```