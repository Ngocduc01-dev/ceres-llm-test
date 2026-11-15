**A. Test paths**

Mã nguồn và CFG khớp nhau. CFG dựng cho N = 2, nên các node giữ nguyên số, còn số lần lặp của node 2 bằng N.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 (N=0, 0 lần lặp) | START → 1 → 2 → 7 → END | node 2: sai |
| P2 (N=1, 1 lần lặp) | START → 1 → 2 → 3 → 4 → 6 → 2 → 7 → END | node 2: đúng, sai; node 4: sai |
| P3 (N=2, 2 lần lặp) | START → 1 → 2 → 3 → 4 → 5 → 6 → 2 → 3 → 4 → 6 → 2 → 7 → END | node 2: đúng, sai; node 4: đúng, sai |
| P4 (N=3, giữa) | START → 1 → (2 → 3 → 4 → 5 → 6) ×2 → 2 → 3 → 4 → 6 → 2 → 7 → END | node 2: đúng, sai; node 4: đúng, sai |
| P5 (N=4, n−1) | START → 1 → (2 → 3 → 4 → 5 → 6) ×3 → 2 → 3 → 4 → 6 → 2 → 7 → END | node 2: đúng, sai; node 4: đúng, sai |
| P6 (N=5, n) | START → 1 → (2 → 3 → 4 → 5 → 6) ×4 → 2 → 3 → 4 → 6 → 2 → 7 → END | node 2: đúng, sai; node 4: đúng, sai |

**B. Bộ test case**

N là tham số template, nên mỗi số lần lặp ứng với một lần khởi tạo `Jet<double, N>` riêng.

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | N = 0; `a` ∈ [−10, 10] | `a` = 3.5 |
| TC2 | P2 | N = 1; `a`, `v[i]` ∈ [−10, 10] | `a` = −2.25, `v` = {7.5} |
| TC3 | P3 | N = 2; `a`, `v[i]` ∈ [−10, 10] | `a` = 1.5, `v` = {−4.0, 6.25} |
| TC4 | P4 | N = 3; `a`, `v[i]` ∈ [−10, 10] | `a` = 8.0, `v` = {2.5, −1.5, 9.0} |
| TC5 | P5 | N = 4; `a`, `v[i]` ∈ [−10, 10] | `a` = −6.5, `v` = {0.5, 3.0, −7.0, 5.5} |
| TC6 | P6 | N = 5; `a`, `v[i]` ∈ [−10, 10] | `a` = 4.75, `v` = {−3.5, 1.0, 6.0, −9.0, 2.0} |

**C. Nhánh không test**

- Không có nhánh không thể đi tới và không có `CHECK`.
- Số lần lặp n+1 không làm được, vì cận vòng lặp là N, cố định lúc biên dịch.
- Giả định: `Jet<double, 0>` ở TC1 biên dịch được vì Eigen cho phép vector kích thước 0. Nếu không biên dịch được, nhánh node 2: sai vẫn được phủ bởi các test còn lại.
- Thêm `<sstream>` để dùng `std::ostringstream`, ngoài hai `#include` ở mục 3.3.

`C2 dự kiến = 4 / 4`

**D. File test**

```cpp
// FILE: u0497_test.cc
#include <sstream>

#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace {

// P1: node 2: sai (0 lần lặp, N=0)
TEST(JetOutputStreamCFT, TC1_ZeroIterations) {
  Jet<double, 0> z;
  z.a = 3.5;
  std::ostringstream os;
  os << z;
}

// P2: node 2: đúng, sai; node 4: sai (1 lần lặp, N=1)
TEST(JetOutputStreamCFT, TC2_OneIteration) {
  Jet<double, 1> z;
  z.a = -2.25;
  z.v[0] = 7.5;
  std::ostringstream os;
  os << z;
}

// P3: node 2: đúng, sai; node 4: đúng, sai (2 lần lặp, N=2)
TEST(JetOutputStreamCFT, TC3_TwoIterations) {
  Jet<double, 2> z;
  z.a = 1.5;
  z.v[0] = -4.0;
  z.v[1] = 6.25;
  std::ostringstream os;
  os << z;
}

// P4: node 2: đúng, sai; node 4: đúng, sai (3 lần lặp, giá trị ở giữa, N=3)
TEST(JetOutputStreamCFT, TC4_MiddleIterations) {
  Jet<double, 3> z;
  z.a = 8.0;
  z.v[0] = 2.5;
  z.v[1] = -1.5;
  z.v[2] = 9.0;
  std::ostringstream os;
  os << z;
}

// P5: node 2: đúng, sai; node 4: đúng, sai (n-1 = 4 lần lặp, N=4)
TEST(JetOutputStreamCFT, TC5_NMinusOneIterations) {
  Jet<double, 4> z;
  z.a = -6.5;
  z.v[0] = 0.5;
  z.v[1] = 3.0;
  z.v[2] = -7.0;
  z.v[3] = 5.5;
  std::ostringstream os;
  os << z;
}

// P6: node 2: đúng, sai; node 4: đúng, sai (n = 5 lần lặp, N=5)
TEST(JetOutputStreamCFT, TC6_NIterations) {
  Jet<double, 5> z;
  z.a = 4.75;
  z.v[0] = -3.5;
  z.v[1] = 1.0;
  z.v[2] = 6.0;
  z.v[3] = -9.0;
  z.v[4] = 2.0;
  std::ostringstream os;
  os << z;
}

}  // namespace
}  // namespace ceres
```