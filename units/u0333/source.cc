// u0333 – ceres::SoftLOneLoss::Evaluate
// Trích từ internal/ceres/loss_function.cc, dòng 66–73 (chỉ để xem, không compile)

void SoftLOneLoss::Evaluate(double s, double rho[3]) const {
  const double sum = 1.0 + s * c_;
  const double tmp = sqrt(sum);
  // 'sum' and 'tmp' are always positive, assuming that 's' is.
  rho[0] = 2.0 * b_ * (tmp - 1.0);
  rho[1] = std::max(std::numeric_limits<double>::min(), 1.0 / tmp);
  rho[2] = -(c_ * rho[1]) / (2.0 * sum);
}
