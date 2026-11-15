**A. Test paths**

Điểm rẽ nhánh duy nhất là node 2 (vòng `for`, `i < kTangentSize`), nên có 2 nhánh: đúng và sai. Số lần lặp bằng `kTangentSize`, cố định theo từng lần khởi tạo template. Vì vậy mỗi test dùng một kích thước khác nhau.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 5 → END | node 2: sai (0 lần lặp) – không thể đi tới |
| P2 | START → 1 → 2 → 3 → 4 → 2 → 5 → END | node 2: đúng, rồi sai (1 lần lặp) |
| P3 | START → 1 → (2 → 3 → 4) ×2 → 2 → 5 → END | node 2: đúng ×2, rồi sai (2 lần lặp) |
| P4 | START → 1 → (2 → 3 → 4) ×3 → 2 → 5 → END | node 2: đúng ×3, rồi sai (3 lần lặp, giá trị ở giữa) |
| P5 | START → 1 → (2 → 3 → 4) ×4 → 2 → 5 → END | node 2: đúng ×4, rồi sai (4 lần lặp) |
| P6 | START → 1 → (2 → 3 → 4) ×5 → 2 → 5 → END | node 2: đúng ×5, rồi sai (5 lần lặp) |

**B. Bộ test case**

Hàm chỉ có tham số `x` (mảng N phần tử) và `jacobian` (ma trận N×N). Giá trị của `x` lấy ngẫu nhiên trong [-1, 1] bằng `std::mt19937` với seed cố định 42. Mảng `jacobian` được khởi tạo bằng 0.

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P2 | kTangentSize = 1; x[i] ∈ [-1, 1] | N = 1, x lấy từ mt19937(42) |
| TC2 | P3 | kTangentSize = 2; x[i] ∈ [-1, 1] | N = 2, x lấy từ mt19937(42) |
| TC3 | P4 | kTangentSize = 3; x[i] ∈ [-1, 1] | N = 3, x lấy từ mt19937(42) |
| TC4 | P5 | kTangentSize = 4; x[i] ∈ [-1, 1] | N = 4, x lấy từ mt19937(42) |
| TC5 | P6 | kTangentSize = 5; x[i] ∈ [-1, 1] | N = 5, x lấy từ mt19937(42) |

**C. Nhánh không test**

- P1 (0 lần lặp): không thể đi tới. `AutoDiffManifold` có `static_assert(kTangentSize > 0)`, nên không thể khởi tạo với `kTangentSize = 0`.
- Không có `CHECK` nào trong hàm.
- n+1 lần lặp: không làm được, vì n là hằng số của template. Các kích thước 1..5 thay thế cho các mức 1, 2, giữa, n−1, n.

`C2 dự kiến = 2 / 2`

**D. File test**

```cpp
// FILE: u0438_test.cc
#include <random>

#include "ceres/autodiff_manifold.h"
#include "gtest/gtest.h"

namespace ceres {
namespace {

// Functor Euclid kích thước N dùng cho AutoDiffManifold.
template <int N>
struct EuclideanFunctorN {
  template <typename T>
  bool operator()(const T* x, const T* delta, T* x_plus_delta) const {
    for (int i = 0; i < N; ++i) {
      x_plus_delta[i] = x[i] + delta[i];
    }
    return true;
  }

  template <typename T>
  bool Minus(const T* y, const T* x, T* y_minus_x) const {
    for (int i = 0; i < N; ++i) {
      y_minus_x[i] = y[i] - x[i];
    }
    return true;
  }
};

// Gọi MinusJacobian một lần với x ngẫu nhiên (seed cố định) trong [-1, 1].
template <int N>
void CallMinusJacobian() {
  std::mt19937 gen(42);
  std::uniform_real_distribution<double> dist(-1.0, 1.0);

  double x[N];
  for (int i = 0; i < N; ++i) {
    x[i] = dist(gen);
  }
  double jacobian[N * N];
  for (int i = 0; i < N * N; ++i) {
    jacobian[i] = 0.0;
  }

  AutoDiffManifold<EuclideanFunctorN<N>, N, N> manifold;
  manifold.MinusJacobian(x, jacobian);
}

// P2: node 2: đúng, rồi sai (1 lần lặp)
TEST(AutoDiffManifoldMinusJacobian, TC1_OneIteration) {
  CallMinusJacobian<1>();
}

// P3: node 2: đúng x2, rồi sai (2 lần lặp)
TEST(AutoDiffManifoldMinusJacobian, TC2_TwoIterations) {
  CallMinusJacobian<2>();
}

// P4: node 2: đúng x3, rồi sai (3 lần lặp)
TEST(AutoDiffManifoldMinusJacobian, TC3_ThreeIterations) {
  CallMinusJacobian<3>();
}

// P5: node 2: đúng x4, rồi sai (4 lần lặp)
TEST(AutoDiffManifoldMinusJacobian, TC4_FourIterations) {
  CallMinusJacobian<4>();
}

// P6: node 2: đúng x5, rồi sai (5 lần lặp)
TEST(AutoDiffManifoldMinusJacobian, TC5_FiveIterations) {
  CallMinusJacobian<5>();
}

}  // namespace
}  // namespace ceres
```