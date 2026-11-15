**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm rẽ nhánh, 0 nhánh). CFG khớp với mã nguồn. Chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh (node 1 là đoạn lệnh tuần tự: `return isless(AsScalar(f), AsScalar(g))`) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f.a`, `g.a` là double bất kỳ (không có điều kiện ràng buộc); `v` là vector 2 phần tử bất kỳ | `f.a = 3.7`, `g.a = 5.2`, `v = {0.5, 1.5}` (cố định, không dùng số ngẫu nhiên) |

**C. Nhánh không test**

Không có nhánh nào (tổng số nhánh = 0). Không có nhánh `CHECK`.

`C2 dự kiến = 0 / 0` (không có nhánh; tương đương 100% vì node 1 và đường START → 1 → END đều được chạy qua).

**D. File test**

```cpp
// FILE: u0136_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetIsLessTest, TC1_P1_SequentialReturn) {
  using JetT = Jet<double, 2>;
  Eigen::Matrix<double, 2, 1> v;
  v << 0.5, 1.5;
  JetT f(3.7, v);
  JetT g(5.2, v);
  // Không kiểm tra kết quả trả về, chỉ gọi hàm một lần.
  (void)isless(f, g);
}

}  // namespace ceres
```