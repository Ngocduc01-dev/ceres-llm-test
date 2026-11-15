**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh; node 1 (`return Jet<T, N>(f.a * s, f.v * s)`) chạy tuần tự |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `s` (double): bất kỳ số thực hữu hạn, chọn trong [-10, 10]; `f` là `Jet<double, 4>` với `f.a` trong [-10, 10] và 4 phần tử `f.v` mỗi phần tử trong [-10, 10]. Không có vòng lặp, không có điều kiện ràng buộc. | `s` = 3.0; `f.a` = 2.0; `f.v` = {1.0, -2.0, 0.5, 4.0} (cố định, không dùng hàm ngẫu nhiên) |

**C. Nhánh không test**

- Không có: hàm không có điểm rẽ nhánh và không có vòng lặp. Không có `CHECK`.
- Tổng số nhánh = 2 × 0 = 0. Một test đi qua toàn bộ đường đi duy nhất (node 1).
- Mã nguồn khớp với CFG.
- `C2 dự kiến = 0 / 0` (không có nhánh; toàn bộ câu lệnh node 1 được chạy, tức phủ 100% câu lệnh).

**D. File test**

```cpp
// FILE: u0086_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetScalarTimesJetTest, P1_ScalarTimesJet) {
  const double s = 3.0;
  Jet<double, 4> f(2.0);
  f.v[0] = 1.0;
  f.v[1] = -2.0;
  f.v[2] = 0.5;
  f.v[3] = 4.0;

  // Gọi unit một lần; không kiểm tra kết quả trả về.
  Jet<double, 4> r = operator*(s, f);
  (void)r;
}

}  // namespace internal
}  // namespace ceres
```