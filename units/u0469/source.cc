// u0469 – ceres::HuberLoss::Evaluate
// Trích từ internal/ceres/loss_function.cc, dòng 50–64 (chỉ để xem, không compile)

void HuberLoss::Evaluate(double s, double rho[3]) const {
  if (s > b_) {
    // Outlier region.
    // 'r' is always positive.
    const double r = sqrt(s);
    rho[0] = 2.0 * a_ * r - b_;
    rho[1] = std::max(std::numeric_limits<double>::min(), a_ / r);
    rho[2] = -rho[1] / (2.0 * s);
  } else {
    // Inlier region.
    rho[0] = s;
    rho[1] = 1.0;
    rho[2] = 0.0;
  }
}
