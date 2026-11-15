**A. Test paths**

Unit không có điểm rẽ nhánh nào (0 điểm rẽ nhánh, 0 nhánh). Chỉ có một đường đi duy nhất. Không có vòng lặp. Không có `CHECK`.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh (đường đi tuần tự duy nhất) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `value`: double bất kỳ (-10 đến 10); `k`: số nguyên 0 đến 3 (hợp lệ với `Jet<double, 4>`) | `value` = 3.5, `k` = 2 (seed cố định, `std::mt19937 gen(42)`) |

Ghi chú: giá trị đã chọn được cố định trực tiếp trong code, không dùng hàm sinh số ngẫu nhiên, nên mỗi lần chạy cho cùng kết quả.

**C. Nhánh không test**

Không có nhánh nào bị bỏ qua (unit không có điểm rẽ nhánh). Mã nguồn khớp với CFG.

`C2 dự kiến = 0 / 0` (không có nhánh nào; đường đi duy nhất P1 được chạy qua, tức 100% câu lệnh).

**D. File test**

```cpp
// FILE: u0070_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetConstructorValueK, TC1_SequentialPath) {
  const double value = 3.5;
  const int k = 2;
  ceres::Jet<double, 4> j(value, k);
  (void)j;
}
```