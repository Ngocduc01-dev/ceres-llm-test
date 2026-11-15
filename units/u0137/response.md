**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào (0 điểm). Hàm chỉ có một đường đi duy nhất. |

CFG khớp với mã nguồn: hàm chỉ có một lệnh `return` ở node 1 và không có vòng lặp.

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f`, `g` là `Jet<double, 2>` bất kỳ. Phần thực nằm trong [-10, 10] và không có điều kiện đường đi nào khác. | `f = Jet<double, 2>(3.7, 0)`, `g = Jet<double, 2>(-1.2, 1)` (giá trị cố định, không dùng sinh số ngẫu nhiên) |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh và không có `CHECK`.

C2 dự kiến = 0 / 0 (tổng số nhánh bằng 0, nên coi như phủ đầy đủ 100% nhờ TC1 đi qua node 1; dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0137_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(IsGreaterJetTest, P1_JetDouble2_SinglePath) {
  const Jet<double, 2> f(3.7, 0);
  const Jet<double, 2> g(-1.2, 1);
  bool result = isgreater(f, g);
  (void)result;  // Không kiểm tra kết quả trả về.
}

}  // namespace ceres
```