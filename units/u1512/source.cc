// u1512 – ceres::Problem::Evaluate
// Trích từ internal/ceres/problem.cc, dòng 128–134 (chỉ để xem, không compile)

bool Problem::Evaluate(const EvaluateOptions& evaluate_options,
                       double* cost,
                       std::vector<double>* residuals,
                       std::vector<double>* gradient,
                       CRSMatrix* jacobian) {
  return impl_->Evaluate(evaluate_options, cost, residuals, gradient, jacobian);
}
