// FILE: u0326_test.cc
#include <map>
#include <memory>
#include <string>

#include "gtest/gtest.h"
#include "ceres/line_search.h"
#include "ceres/evaluator.h"

namespace ceres {
namespace internal {

namespace {

// Evaluator giả, chỉ cung cấp số chiều cho constructor của LineSearchFunction.
class FakeEvaluator : public Evaluator {
 public:
  explicit FakeEvaluator(int n) : n_(n) {}

  std::unique_ptr<SparseMatrix> CreateJacobian() const final {
    return nullptr;
  }

  bool Evaluate(const EvaluateOptions& evaluate_options,
                const double* state,
                double* cost,
                double* residuals,
                double* gradient,
                SparseMatrix* jacobian) final {
    return true;
  }

  bool Plus(const double* state,
            const double* delta,
            double* state_plus_delta) const final {
    return true;
  }

  int NumParameters() const final { return n_; }
  int NumEffectiveParameters() const final { return n_; }
  int NumResiduals() const final { return n_; }

 private:
  int n_;
};

}  // namespace

// TC1 - Path P1: START -> 1 -> END (không có nhánh rẽ)
TEST(LineSearchFunctionDirectionTest, P1_ReturnDirection) {
  FakeEvaluator evaluator(3);
  LineSearchFunction function(&evaluator);
  const Vector& direction = function.direction();
  (void)direction;
}

}  // namespace internal
}  // namespace ceres
