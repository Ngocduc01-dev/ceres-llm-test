// u0470 – ceres::TolerantLoss::Evaluate
// Trích từ internal/ceres/loss_function.cc, dòng 99–118 (chỉ để xem, không compile)

void TolerantLoss::Evaluate(double s, double rho[3]) const {
  const double x = (s - a_) / b_;
  // The basic equation is rho[0] = b ln(1 + e^x).  However, if e^x is too
  // large, it will overflow.  Since numerically 1 + e^x == e^x when the
  // x is greater than about ln(2^53) for doubles, beyond this threshold
  // we substitute x for ln(1 + e^x) as a numerically equivalent approximation.

  // ln(MathLimits<double>::kEpsilon).
  static constexpr double kLog2Pow53 = 36.7;
  if (x > kLog2Pow53) {
    rho[0] = s - a_ - c_;
    rho[1] = 1.0;
    rho[2] = 0.0;
  } else {
    const double e_x = exp(x);
    rho[0] = b_ * log(1.0 + e_x) - c_;
    rho[1] = std::max(std::numeric_limits<double>::min(), e_x / (1.0 + e_x));
    rho[2] = 0.5 / (b_ * (1.0 + cosh(x)));
  }
}
