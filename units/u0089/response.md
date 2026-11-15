**A. Test paths**

Hàm có 0 điểm rẽ nhánh và không có vòng lặp, nên chỉ có một đường đi.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

Ghi chú: CFG đã cho không khớp mã nguồn. CFG dùng `g.a` và `f_a_by_g_a`, còn mã nguồn dùng `s` và `s_inverse`, đồng thời trả về `Jet(f.a * s_inverse, f.v * s_inverse)`. Tôi theo mã nguồn. Node 1 tương ứng với dòng 390–391.

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f.a` ∈ [-5, 5]; `f.v` là vector 3 phần tử (đạo hàm theo biến thứ 1, tức `Jet(a, 1)`); `s` ∈ [1, 5] (hàm không rẽ nhánh nên `s` không bị ràng buộc, chọn khác 0 để tránh chia cho 0) | `f.a` = 1.5, `k` = 1, `s` = 2.0 (giá trị cố định, không dùng số ngẫu nhiên nên không cần seed) |

**C. Nhánh không test**

Không có nhánh nào bị bỏ qua, vì hàm không có điểm rẽ nhánh. Không có nhánh `CHECK`.

C2 dự kiến = 0 / 0 (không có nhánh nào cần phủ, node 1 đã được chạy qua nên coi như đạt 100%).

**D. File test**

```cpp
// FILE: u0089_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetOperatorDivideScalarTest, TC1_P1_DivideJetByScalar) {
  const Jet<double, 3> f(1.5, 1);
  const double s = 2.0;
  Jet<double, 3> r = f / s;
  (void)r;
}

}  // namespace
}  // namespace ceres
```