**A. Test paths**

Hàm không có điểm rẽ nhánh (0 điểm rẽ nhánh, tổng số nhánh = 0). Hai lệnh `CHECK` không được tính nhánh. Chỉ có một đường đi hợp lệ:

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → END | node 2: đúng (CHECK_GE), node 3: đúng (CHECK_GT) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | a ≥ 0.0 (chọn a trong [0, 5]); b > 0.0 (chọn b trong (0, 5]) | a = 2.5, b = 1.5 |

**C. Nhánh không test**

- Node 2 sai (`CHECK_GE(a, 0.0)` sai) → không test (làm chương trình dừng).
- Node 3 sai (`CHECK_GT(b, 0.0)` sai) → không test (làm chương trình dừng).
- Hai nhánh này là nhánh của `CHECK`, không tính vào tổng số nhánh.

C2 dự kiến = 0 / 0 (hàm không có điểm rẽ nhánh nên không có nhánh nào để tính; test TC1 đi hết đường duy nhất START → END).

**D. File test**

```cpp
// FILE: u0507_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

// Path P1: START -> 1 -> 2 (đúng) -> 3 (đúng) -> END
TEST(TolerantLossConstructor, ValidParameters) {
  ceres::TolerantLoss loss(2.5, 1.5);
}
```