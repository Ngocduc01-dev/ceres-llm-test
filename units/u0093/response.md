**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm, 0 nhánh), nên chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f` = `Jet<double, 2>` có phần scalar bất kỳ (khoảng 1 đến 5), `g` = `int` bất kỳ (khoảng 1 đến 5). Không có điều kiện đường đi nào ràng buộc thêm. | `f = Jet<double, 2>(3.0, 0)`, `g = 2` |

**C. Nhánh không test**

Không có nhánh nào bị bỏ. Hàm không có điểm rẽ nhánh nên tổng số nhánh là 0.

Ghi chú: mã nguồn là macro `CERES_DEFINE_JET_COMPARISON_OPERATOR(>=)`, và CFG khớp với bản template `Jet` so với scalar kiểu `int`. Test dùng đúng bản này.

C2 dự kiến = 0 / 0 (không có nhánh nào cần phủ, coi như đạt 100%; dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0093_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetOperatorGreaterEqual, JetWithIntScalar) {
  const Jet<double, 2> f(3.0, 0);
  const int g = 2;
  bool result = (f >= g);
  (void)result;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
```