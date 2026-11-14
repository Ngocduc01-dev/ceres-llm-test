// u0765 – ceres::internal::LowRankInverseHessian::Update
// Trích từ internal/ceres/low_rank_inverse_hessian.cc, dòng 87–115 (chỉ để xem, không compile)

bool LowRankInverseHessian::Update(const Vector& delta_x,
                                   const Vector& delta_gradient) {
  const double delta_x_dot_delta_gradient = delta_x.dot(delta_gradient);
  if (delta_x_dot_delta_gradient <=
      kLBFGSSecantConditionHessianUpdateTolerance) {
    VLOG(2) << "Skipping L-BFGS Update, delta_x_dot_delta_gradient too "
            << "small: " << delta_x_dot_delta_gradient
            << ", tolerance: " << kLBFGSSecantConditionHessianUpdateTolerance
            << " (Secant condition).";
    return false;
  }

  int next = indices_.size();
  // Once the size of the list reaches max_num_corrections_, simulate
  // a circular buffer by removing the first element of the list and
  // making it the next position where the LBFGS history is stored.
  if (next == max_num_corrections_) {
    next = indices_.front();
    indices_.pop_front();
  }

  indices_.push_back(next);
  delta_x_history_.col(next) = delta_x;
  delta_gradient_history_.col(next) = delta_gradient;
  delta_x_dot_delta_gradient_(next) = delta_x_dot_delta_gradient;
  approximate_eigenvalue_scale_ =
      delta_x_dot_delta_gradient / delta_gradient.squaredNorm();
  return true;
}
