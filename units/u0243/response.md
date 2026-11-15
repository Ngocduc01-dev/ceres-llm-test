**A. Test paths**

Unit không có điểm rẽ nhánh nào (CFG khớp mã nguồn), nên chỉ có một đường đi.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Hàm không có tham số, không có đầu vào | Không có |

**C. Nhánh không test**

Không có. Tổng số nhánh là 0, nên mọi nhánh (không có nhánh nào) đều được phủ bởi TC1.

`C2 dự kiến = 0 / 0` (không có nhánh nào, coi như đạt 100%; mới dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0243_test.cc
#include "gtest/gtest.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(CeresInitTest, P1_StraightLine) {
  ceres_init();
}
```