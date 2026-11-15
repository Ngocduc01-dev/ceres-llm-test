**A. Test paths**

Unit không có điểm rẽ nhánh nào (0 điểm rẽ nhánh, 0 vòng lặp). CFG chỉ có một đường đi duy nhất.

Ghi chú: CFG chỉ ghi `operator*`, nhưng mã nguồn còn có lời gọi `BesselJn` cho `double`, phép trừ và constructor `Jet`. Tất cả đều là lệnh tuần tự, không rẽ nhánh, nên không ảnh hưởng đến kết quả.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh nào (không có điểm rẽ nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `n` ∈ [1, 5]; `f.a` ∈ [0.5, 5.0]; `f.v` là vector 2 phần tử, bất kỳ | `n = 3`; `f.a = 2.7`; `f.v = (1, 0)` (do constructor `Jet(a, 0)` tạo ra) |

**C. Nhánh không test**

Không có nhánh nào bị bỏ qua. `CHECK` không xuất hiện trong unit.

`C2 dự kiến = 0 / 0` (không có nhánh nào, nên mặc định coi là phủ đầy đủ 100%; dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0131_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(BesselJnJetTest, SinglePathNoBranch) {
  const int n = 3;
  const Jet<double, 2> f(2.7, 0);
  Jet<double, 2> result = BesselJn(n, f);
  (void)result;  // Không kiểm tra kết quả trả về.
}

}  // namespace internal
}  // namespace ceres
```