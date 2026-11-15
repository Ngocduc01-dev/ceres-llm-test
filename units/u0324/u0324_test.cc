// FILE: u0324_test.cc
#include <memory>

#include "gtest/gtest.h"
#include "ceres/line_search.h"
#include "ceres/evaluator.h"  // cần để định nghĩa evaluator giả (line_search.h chỉ khai báo trước Evaluator)

namespace ceres {
namespace internal {

namespace {

// Evaluator giả, chỉ cung cấp số chiều tham số cho constructor của LineSearchFunction.
class FakeEvaluator : public Evaluator {
 public:
  FakeEvaluator(int num_parameters, int num_effective_parameters)
      : num_parameters_(num_parameters),
        num_effective_parameters_(num_effective_parameters) {}

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

  int NumParameters() const final { return num_parameters_; }
  int NumEffectiveParameters() const final { return num_effective_parameters_; }
  int NumResiduals() const final { return 1; }

 private:
  int num_parameters_;
  int num_effective_parameters_;
};

}  // namespace

// TC1 - P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(LineSearchFunctionDirectionInfinityNormTest, P1_SingleStatementPath) {
  FakeEvaluator evaluator(3, 3);
  LineSearchFunction function(&evaluator);
  function.DirectionInfinityNorm();
}

}  // namespace internal
}  // namespace ceres
