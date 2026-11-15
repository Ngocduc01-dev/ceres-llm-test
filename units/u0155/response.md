**CFG của unit**

- Điểm rẽ nhánh: không có (không có `if`, vòng lặp, `switch`, `?:`).
- CFG: `START → 1 → END`
- Node 1: dòng 1343, `return ceres::Jet<T, N>(std::numeric_limits<T>::infinity());`
- Tổng số nhánh = 2 × 0 = 0.

**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có tham số đầu vào. Chỉ cần chọn kiểu `T`, `N` cụ thể. | `T = double`, `N = 2` (cố định, không dùng số ngẫu nhiên) |

**C. Nhánh không test**

Không có nhánh nào bị bỏ qua.

`C2 dự kiến = 0 / 0` (hàm không có nhánh, nên chỉ cần chạy qua node 1 là phủ toàn bộ; coi như 100%, dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0155_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(NumericLimitsJetInfinity, TC1_P1_DoubleN2) {
  std::numeric_limits<ceres::Jet<double, 2>> obj;
  ceres::Jet<double, 2> result = obj.infinity();
  (void)result;  // Không kiểm tra kết quả trả về
}
```