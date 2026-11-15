**A. Test paths**

Hàm có 0 điểm rẽ nhánh nên chỉ có một đường đi. CFG khớp với mã nguồn (một câu lệnh `return`, gồm lời gọi `norm(f.a)` và phép `operator*`).

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f.a` ∈ [-10, 10]; `f.v[0]`, `f.v[1]` ∈ [-10, 10]. Không có điều kiện đường đi nào ràng buộc thêm. | `f.a = 3.0`, `f.v = (-2.0, 4.0)` |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh và không có `CHECK`.

`C2 dự kiến = 0 / 0` (không có nhánh nào cần phủ; coi như đạt 100%, chạy một lần là đi hết hàm).

**D. File test**

```cpp
// FILE: u0149_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (hàm không có điểm rẽ nhánh)
TEST(JetNormTest, P1_SingleStatementPath) {
  Jet<double, 2> f;
  f.a = 3.0;
  f.v[0] = -2.0;
  f.v[1] = 4.0;

  Jet<double, 2> r = ceres::norm(f);
  (void)r;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
```