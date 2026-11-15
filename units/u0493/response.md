**A. Test paths**

Hàm có 2 điểm rẽ nhánh (node 2 và node 6), tổng cộng 4 nhánh. Mỗi test dùng một cặp kích thước cố định (kAmbientSize = kTangentSize = N). Vòng lặp ở node 2 và node 6 đều lặp đúng N lần, nên số lần lặp được điều khiển bằng cách chọn N.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 (N=1) | START → 1 → 2 → 3 → 4 → 2 → 5 → 6 → 7 → 8 → 6 → 9 → END | node 2: đúng ×1, sai; node 6: đúng ×1, sai |
| P2 (N=2) | START → 1 → (2→3→4)×2 → 2 → 5 → (6→7→8)×2 → 6 → 9 → END | node 2: đúng ×2, sai; node 6: đúng ×2, sai |
| P3 (N=3) | tương tự, lặp 3 lần | node 2: đúng ×3, sai; node 6: đúng ×3, sai |
| P4 (N=4) | tương tự, lặp 4 lần (n−1) | node 2: đúng ×4, sai; node 6: đúng ×4, sai |
| P5 (N=5) | tương tự, lặp 5 lần (n) | node 2: đúng ×5, sai; node 6: đúng ×5, sai |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | N = 1; x[0] ∈ [−5, 5] | x = {1.5} |
| TC2 | P2 | N = 2; x[i] ∈ [−5, 5] | x = {−2.0, 0.5} |
| TC3 | P3 | N = 3; x[i] ∈ [−5, 5] | x = {0.7, −1.3, 2.4} |
| TC4 | P4 | N = 4; x[i] ∈ [−5, 5] | x = {3.1, −0.4, 1.2, −2.8} |
| TC5 | P5 | N = 5; x[i] ∈ [−5, 5] | x = {0.3, 1.1, −4.2, 2.6, −0.9} |

**C. Nhánh không test**

- Không có nhánh nào không thể đi tới và không có `CHECK` trong unit.
- Số lần lặp 0 không làm được. Số lần lặp là hằng số biên dịch N, và mảng kích thước 0 không hợp lệ trong C++ chuẩn.
- Số lần lặp n+1 không làm được, vì n chính là kích thước mảng.
- Các giá trị 1, 2, 3 (giữa), 4 (n−1), 5 (n) được phủ bằng cách đổi N giữa các test. Đây là các instantiation khác nhau của template.

`C2 dự kiến = 4 / 4`

**D. File test**

```cpp
// FILE: u0493_test.cc
#include "gtest/gtest.h"
#include "ceres/autodiff_manifold.h"

namespace ceres {
namespace {

// Manifold Euclid: Plus(x, delta) = x + delta
template <int N>
struct TestPlusFunctor {
  template <typename T>
  bool operator()(const T* x, const T* delta, T* x_plus_delta) const {
    for (int i = 0; i < N; ++i) {
      x_plus_delta[i] = x[i] + delta[i];
    }
    return true;
  }
};

// Path P1: node 2: đúng x1, sai; node 6: đúng x1, sai (N = 1)
TEST(AutoDiffManifoldPlusJacobian, TC1_N1) {
  AutoDiffManifold<TestPlusFunctor<1>, 1, 1> manifold(
      new TestPlusFunctor<1>());
  const double x[1] = {1.5};
  double jacobian[1] = {0.0};
  manifold.PlusJacobian(x, jacobian);
}

// Path P2: node 2: đúng x2, sai; node 6: đúng x2, sai (N = 2)
TEST(AutoDiffManifoldPlusJacobian, TC2_N2) {
  AutoDiffManifold<TestPlusFunctor<2>, 2, 2> manifold(
      new TestPlusFunctor<2>());
  const double x[2] = {-2.0, 0.5};
  double jacobian[4] = {0.0, 0.0, 0.0, 0.0};
  manifold.PlusJacobian(x, jacobian);
}

// Path P3: node 2: đúng x3, sai; node 6: đúng x3, sai (N = 3)
TEST(AutoDiffManifoldPlusJacobian, TC3_N3) {
  AutoDiffManifold<TestPlusFunctor<3>, 3, 3> manifold(
      new TestPlusFunctor<3>());
  const double x[3] = {0.7, -1.3, 2.4};
  double jacobian[9] = {0.0};
  manifold.PlusJacobian(x, jacobian);
}

// Path P4: node 2: đúng x4, sai; node 6: đúng x4, sai (N = 4)
TEST(AutoDiffManifoldPlusJacobian, TC4_N4) {
  AutoDiffManifold<TestPlusFunctor<4>, 4, 4> manifold(
      new TestPlusFunctor<4>());
  const double x[4] = {3.1, -0.4, 1.2, -2.8};
  double jacobian[16] = {0.0};
  manifold.PlusJacobian(x, jacobian);
}

// Path P5: node 2: đúng x5, sai; node 6: đúng x5, sai (N = 5)
TEST(AutoDiffManifoldPlusJacobian, TC5_N5) {
  AutoDiffManifold<TestPlusFunctor<5>, 5, 5> manifold(
      new TestPlusFunctor<5>());
  const double x[5] = {0.3, 1.1, -4.2, 2.6, -0.9};
  double jacobian[25] = {0.0};
  manifold.PlusJacobian(x, jacobian);
}

}  // namespace
}  // namespace ceres
```