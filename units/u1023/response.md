# A. Test paths

| Path | Đường đi (node) | Nhánh |
|---|---|---|
| P1 | START → 1 → END | Theo CFG/source; case 1 |

# B. Test cases

| Test | Path | Dữ liệu đã chọn |
|---|---|---|
| TC1 | P1 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |

# C. Nhánh không test

Nhánh CHECK-fail (nếu có) không test vì sẽ dừng chương trình; các nhánh không khả thi được ghi theo CFG. Không có cfg.txt; không bịa CFG/C2.

C2 dự kiến = không xác định vì thiếu cfg.txt; không bịa nhánh (chưa chạy thật).

# D. File test

```cpp
// FILE: u1023_test.cc
#include "gtest/gtest.h"
#include "ceres/stringprintf.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1023, TC1_CallsTarget) {
  ceres::internal::StringPrintf(nullptr);
}
```
