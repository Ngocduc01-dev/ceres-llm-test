// u0335 – ceres::ArctanLoss::Evaluate
// Trích từ internal/ceres/loss_function.cc, dòng 84–91 (chỉ để xem, không compile)

void ArctanLoss::Evaluate(double s, double rho[3]) const {
  const double sum = 1 + s * s * b_;
  const double inv = 1 / sum;
  // 'sum' and 'inv' are always positive.
  rho[0] = a_ * atan2(s, a_);
  rho[1] = std::max(std::numeric_limits<double>::min(), inv);
  rho[2] = -2.0 * s * b_ * (inv * inv);
}
