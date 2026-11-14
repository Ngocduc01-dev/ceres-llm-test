// u1049 – ceres::GradientProblem::Evaluate
// Trích từ internal/ceres/gradient_problem.cc, dòng 68–78 (chỉ để xem, không compile)

bool GradientProblem::Evaluate(const double* parameters,
                               double* cost,
                               double* gradient) const {
  if (gradient == nullptr) {
    return function_->Evaluate(parameters, cost, nullptr);
  }

  return (function_->Evaluate(parameters, cost, scratch_.get()) &&
          manifold_->RightMultiplyByPlusJacobian(
              parameters, 1, scratch_.get(), gradient));
}
