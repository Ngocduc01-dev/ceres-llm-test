**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm rẽ nhánh, 0 nhánh, 0 vòng lặp). CFG chỉ có một node 1 (khớp với mã nguồn), nên chỉ có một đường đi.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh nào (không có điểm rẽ nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `value` kiểu `double`: bất kỳ giá trị hữu hạn nào (không có điều kiện đường đi ràng buộc) | `value = 2.5` (cố định, không dùng sinh số ngẫu nhiên nên không cần seed) |

**C. Nhánh không test**

Không có nhánh nào bị bỏ qua: không có điểm rẽ nhánh, không có `CHECK`, không có vòng lặp.

`C2 dự kiến = 0 / 0` (tổng số nhánh bằng 0, nên mọi câu lệnh đã được phủ khi đi qua P1).

**D. File test**

```cpp
// FILE: u0069_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetConstructorValueTest, P1_ConstructFromValue) {
  const double value = 2.5;
  ceres::Jet<double, 4> jet(value);
  (void)jet;
}
```