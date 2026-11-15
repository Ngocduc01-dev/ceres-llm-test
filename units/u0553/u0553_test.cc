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
