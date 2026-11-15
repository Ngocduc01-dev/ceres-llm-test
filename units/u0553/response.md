**A. Test paths**

Các điểm rẽ nhánh: node 1, 2, 4, 6, 9, 11 (6 điểm, 12 nhánh).

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → END | node 1: đúng, node 2: đúng |
| P2 | START → 1 → 15 → 4 → 9 → 14 → END | node 1: sai, node 4: sai, node 9: sai |
| P3 | START → 1 → 2 → 4 → 5 → (6 → 7 → 8)×1 → 6 → 9 → 10 → (11 → 12 → 13)×1 → 11 → 14 → END | node 1: đúng, node 2: sai, node 4: đúng, node 6: đúng×1 rồi sai, node 9: đúng, node 11: đúng×1 rồi sai |
| P4 | START → 1 → 15 → 4 → 5 → (6 → 7 → 8)×2 → 6 → 9 → 10 → (11 → 12 → 13)×2 → 11 → 14 → END | node 1: sai, node 4: đúng, node 6: đúng×2 rồi sai, node 9: đúng, node 11: đúng×2 rồi sai |
| P5 | Như P3 nhưng lặp ×3 ở cả hai vòng for | node 1: đúng, node 2: sai, node 4: đúng, node 6: đúng×3 rồi sai, node 9: đúng, node 11: đúng×3 rồi sai |
| P6 | Như P4 nhưng lặp ×5 ở cả hai vòng for | node 1: sai, node 4: đúng, node 6: đúng×5 rồi sai, node 9: đúng, node 11: đúng×5 rồi sai |

**B. Bộ test case**

Số lần lặp của vòng for bằng `size_`. Khi có bound, `size_` ≥ 1 vì `SetLowerBound` và `SetUpperBound` yêu cầu `index < size_`. Vì vậy các số lần lặp thử là 1, 2, 3 (giữa), 5 (tối đa, n). Số lần lặp bằng 0 và n+1 không làm được (xem mục C).

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | manifold có `Plus` trả về false; size = 2; x, delta ∈ [-5, 5] | size = 2; x, delta lấy từ mt19937 seed 1 |
| TC2 | P2 | manifold = nullptr; không đặt bound; size ∈ [1, 5]; x, delta ∈ [-5, 5] | size = 3; x, delta lấy từ mt19937 seed 2 |
| TC3 | P3 | manifold `EuclideanManifold<1>`; size = 1 (1 lần lặp); lower ∈ [-10, -6]; upper ∈ [6, 10] | size = 1; giá trị lấy từ seed 3 |
| TC4 | P4 | manifold = nullptr; size = 2 (2 lần lặp); lower, upper như trên | size = 2; giá trị lấy từ seed 4 |
| TC5 | P5 | manifold `EuclideanManifold<3>`; size = 3 (số giữa); lower, upper như trên | size = 3; giá trị lấy từ seed 5 |
| TC6 | P6 | manifold = nullptr; size = 5 (n); lower, upper như trên | size = 5; giá trị lấy từ seed 6 |

**C. Nhánh không test**

- Node 6 và node 11 với 0 lần lặp: không làm được. Khi `lower_bounds_` hoặc `upper_bounds_` khác null thì `size_` ≥ 1, vì `SetLowerBound` và `SetUpperBound` có `CHECK` với `index < size_`. Cả hai nhánh "sai" của node 6 và node 11 vẫn được phủ khi thoát vòng lặp sau n lần.
- Số lần lặp n+1: không làm được vì số lần lặp bằng `size_`, cố định theo block.
- Số lần lặp n−1: được phủ gián tiếp bởi các size khác nhau (1, 2, 3, 5); không có test riêng cho size = 4.
- Không có nhánh nào bị bỏ vì thuộc `CHECK`.

C2 dự kiến = 12 / 12

**D. File test**

```cpp
// FILE: u0553_test.cc
#include <random>

#include "gtest/gtest.h"
#include "ceres/manifold.h"
#include "ceres/parameter_block.h"

namespace ceres {
namespace internal {

namespace {

// Manifold giả: Plus luôn trả về false (dùng cho node 2 đúng).
class FailingManifold final : public Manifold {
 public:
  explicit FailingManifold(int size) : size_(size) {}
  int AmbientSize() const override { return size_; }
  int TangentSize() const override { return size_; }
  bool Plus(const double* x,
            const double* delta,
            double* x_plus_delta) const override {
    return false;
  }
  bool PlusJacobian(const double* x, double* jacobian) const override {
    return true;
  }
  bool RightMultiplyByPlusJacobian(const double* x,
                                   const int num_rows,
                                   const double* ambient_matrix,
                                   double* tangent_matrix) const override {
    return true;
  }
  bool Minus(const double* y,
             const double* x,
             double* y_minus_x) const override {
    return true;
  }
  bool MinusJacobian(const double* x, double* jacobian) const override {
    return true;
  }

 private:
  int size_;
};

}  // namespace

// P1: node 1: đúng, node 2: đúng -> return false
TEST(ParameterBlockPlusTest, TC1_ManifoldPlusFails) {
  std::mt19937 gen(1);
  std::uniform_real_distribution<double> dist(-5.0, 5.0);
  const int size = 2;
  double x[2] = {dist(gen), dist(gen)};
  double delta[2] = {dist(gen), dist(gen)};
  double x_plus_delta[2] = {0.0, 0.0};
  FailingManifold manifold(size);
  ParameterBlock block(x, size, -1, &manifold);
  block.Plus(x, delta, x_plus_delta);
}

// P2: node 1: sai, node 4: sai, node 9: sai -> return true
TEST(ParameterBlockPlusTest, TC2_NoManifoldNoBounds) {
  std::mt19937 gen(2);
  std::uniform_real_distribution<double> dist(-5.0, 5.0);
  const int size = 3;
  double x[3] = {dist(gen), dist(gen), dist(gen)};
  double delta[3] = {dist(gen), dist(gen), dist(gen)};
  double x_plus_delta[3] = {0.0, 0.0, 0.0};
  ParameterBlock block(x, size, -1);
  block.Plus(x, delta, x_plus_delta);
}

// P3: node 1: đúng, node 2: sai, node 4: đúng, node 6: đúng x1 rồi sai,
//     node 9: đúng, node 11: đúng x1 rồi sai
TEST(ParameterBlockPlusTest, TC3_ManifoldBoundsSize1) {
  std::mt19937 gen(3);
  std::uniform_real_distribution<double> dist(-5.0, 5.0);
  std::uniform_real_distribution<double> lower_dist(-10.0, -6.0);
  std::uniform_real_distribution<double> upper_dist(6.0, 10.0);
  const int size = 1;
  double x[1] = {dist(gen)};
  double delta[1] = {dist(gen)};
  double x_plus_delta[1] = {0.0};
  EuclideanManifold<1> manifold;
  ParameterBlock block(x, size, -1, &manifold);
  block.SetLowerBound(0, lower_dist(gen));
  block.SetUpperBound(0, upper_dist(gen));
  block.Plus(x, delta, x_plus_delta);
}

// P4: node 1: sai, node 4: đúng, node 6: đúng x2 rồi sai,
//     node 9: đúng, node 11: đúng x2 rồi sai
TEST(ParameterBlockPlusTest, TC4_NoManifoldBoundsSize2) {
  std::mt19937 gen(4);
  std::uniform_real_distribution<double> dist(-5.0, 5.0);
  std::uniform_real_distribution<double> lower_dist(-10.0, -6.0);
  std::uniform_real_distribution<double> upper_dist(6.0, 10.0);
  const int size = 2;
  double x[2] = {dist(gen), dist(gen)};
  double delta[2] = {dist(gen), dist(gen)};
  double x_plus_delta[2] = {0.0, 0.0};
  ParameterBlock block(x, size, -1);
  for (int i = 0; i < size; ++i) {
    block.SetLowerBound(i, lower_dist(gen));
    block.SetUpperBound(i, upper_dist(gen));
  }
  block.Plus(x, delta, x_plus_delta);
}

// P5: node 1: đúng, node 2: sai, node 4: đúng, node 6: đúng x3 rồi sai,
//     node 9: đúng, node 11: đúng x3 rồi sai
TEST(ParameterBlockPlusTest, TC5_ManifoldBoundsSize3) {
  std::mt19937 gen(5);
  std::uniform_real_distribution<double> dist(-5.0, 5.0);
  std::uniform_real_distribution<double> lower_dist(-10.0, -6.0);
  std::uniform_real_distribution<double> upper_dist(6.0, 10.0);
  const int size = 3;
  double x[3] = {dist(gen), dist(gen), dist(gen)};
  double delta[3] = {dist(gen), dist(gen), dist(gen)};
  double x_plus_delta[3] = {0.0, 0.0, 0.0};
  EuclideanManifold<3> manifold;
  ParameterBlock block(x, size, -1, &manifold);
  for (int i = 0; i < size; ++i) {
    block.SetLowerBound(i, lower_dist(gen));
    block.SetUpperBound(i, upper_dist(gen));
  }
  block.Plus(x, delta, x_plus_delta);
}

// P6: node 1: sai, node 4: đúng, node 6: đúng x5 rồi sai,
//     node 9: đúng, node 11: đúng x5 rồi sai
TEST(ParameterBlockPlusTest, TC6_NoManifoldBoundsSize5) {
  std::mt19937 gen(6);
  std::uniform_real_distribution<double> dist(-5.0, 5.0);
  std::uniform_real_distribution<double> lower_dist(-10.0, -6.0);
  std::uniform_real_distribution<double> upper_dist(6.0, 10.0);
  const int size = 5;
  double x[5] = {dist(gen), dist(gen), dist(gen), dist(gen), dist(gen)};
  double delta[5] = {dist(gen), dist(gen), dist(gen), dist(gen), dist(gen)};
  double x_plus_delta[5] = {0.0, 0.0, 0.0, 0.0, 0.0};
  ParameterBlock block(x, size, -1);
  for (int i = 0; i < size; ++i) {
    block.SetLowerBound(i, lower_dist(gen));
    block.SetUpperBound(i, upper_dist(gen));
  }
  block.Plus(x, delta, x_plus_delta);
}

}  // namespace internal
}  // namespace ceres
```