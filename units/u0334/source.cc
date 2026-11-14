// u0334 – ceres::CauchyLoss::Evaluate
// Trích từ internal/ceres/loss_function.cc, dòng 75–82 (chỉ để xem, không compile)

void CauchyLoss::Evaluate(double s, double rho[3]) const {
  const double sum = 1.0 + s * c_;
  const double inv = 1.0 / sum;
  // 'sum' and 'inv' are always positive, assuming that 's' is.
  rho[0] = b_ * log(sum);
  rho[1] = std::max(std::numeric_limits<double>::min(), inv);
  rho[2] = -c_ * (inv * inv);
}
