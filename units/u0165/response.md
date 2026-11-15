**A. Test paths**

CFG: `START → 1 → END`
- Node 1: `return Real(-(std::numeric_limits<T>::max)());`, một khối lệnh chạy thẳng.
- Hàm không có `if`, `for`, `while`, `switch` hay `?:`, nên có 0 điểm rẽ nhánh và 0 nhánh.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Hàm không có tham số. Chỉ cần chọn kiểu template: `T` là kiểu số thực, `N` ≥ 1 | `T = double`, `N = 2` (cố định, không dùng số ngẫu nhiên) |

**C. Nhánh không test**

Không có. Hàm không có nhánh nào và không có `CHECK`.

`C2 dự kiến = 0 / 0` (hàm không có điểm rẽ nhánh nên mọi lần gọi đều đi hết đường đi duy nhất, coi như 100%).

**D. File test**

```cpp
// FILE: u0165_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(NumTraitsJetLowest, StraightLinePath) {
  using JetType = ceres::Jet<double, 2>;
  Eigen::NumTraits<JetType> obj;
  JetType result = obj.lowest();
  (void)result;  // Không kiểm tra kết quả trả về
}
```