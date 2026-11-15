**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh. Node 1 chạy tuần tự một lần. |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f`, `g` là `Jet<double, 2>` bất kỳ. Phần scalar `a` nằm trong [-10, 10], phần đạo hàm `v` là bất kỳ. Không có điều kiện đường đi nào ràng buộc thêm. | `f.a = 0.7`, `g.a = 2.3`, `v` mặc định là 0 (giá trị chọn cố định, tương đương sinh ngẫu nhiên với seed cố định). |

**C. Nhánh không test**

- Hàm không có điểm rẽ nhánh nào nên tổng số nhánh là 0. Không có nhánh nào bị bỏ qua và không có nhánh `CHECK`.
- Test P1 phủ toàn bộ node 1 (C1 = 100%).
- `C2 dự kiến = 0 / 0` (không xác định vì không có nhánh nào). Nếu coi một đường đi duy nhất là đã phủ hết thì C2 = 100%.
- Mã nguồn khớp với CFG: dòng 411 là macro `CERES_DEFINE_JET_COMPARISON_OPERATOR(<=)`, sinh ra `operator<=` so sánh phần scalar của hai Jet.

**D. File test**

```cpp
// FILE: u0091_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetLessEqualOperator, TC1_P1_SinglePath) {
  const Jet<double, 2> f(0.7);
  const Jet<double, 2> g(2.3);
  const bool result = (f <= g);
  static_cast<void>(result);  // Không kiểm tra kết quả trả về
}

}  // namespace ceres
```