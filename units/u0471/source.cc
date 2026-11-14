// u0471 – ceres::TukeyLoss::Evaluate
// Trích từ internal/ceres/loss_function.cc, dòng 120–134 (chỉ để xem, không compile)

void TukeyLoss::Evaluate(double s, double* rho) const {
  if (s <= a_squared_) {
    // Inlier region.
    const double value = 1.0 - s / a_squared_;
    const double value_sq = value * value;
    rho[0] = a_squared_ / 3.0 * (1.0 - value_sq * value);
    rho[1] = value_sq;
    rho[2] = -2.0 / a_squared_ * value;
  } else {
    // Outlier region.
    rho[0] = a_squared_ / 3.0;
    rho[1] = 0.0;
    rho[2] = 0.0;
  }
}
