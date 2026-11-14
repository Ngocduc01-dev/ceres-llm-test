// u0858 – ceres::internal::Evaluator::Evaluate
// Trích từ internal/ceres/evaluator.h, dòng 126–133 (chỉ để xem, không compile)

  bool Evaluate(const double* state,
                double* cost,
                double* residuals,
                double* gradient,
                SparseMatrix* jacobian) {
    return Evaluate(
        EvaluateOptions(), state, cost, residuals, gradient, jacobian);
  }
