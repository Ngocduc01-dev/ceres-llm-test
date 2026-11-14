// u0305 – ceres::GradientProblem::Plus
// Trích từ internal/ceres/gradient_problem.cc, dòng 80–84 (chỉ để xem, không compile)

bool GradientProblem::Plus(const double* x,
                           const double* delta,
                           double* x_plus_delta) const {
  return manifold_->Plus(x, delta, x_plus_delta);
}
