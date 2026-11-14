// u0018 – ceres::BiCubicInterpolator::Evaluate
// Trích từ include/ceres/cubic_interpolation.h, dòng 330–332 (chỉ để xem, không compile)

  void Evaluate(const double& r, const double& c, double* f) const {
    Evaluate(r, c, f, nullptr, nullptr);
  }
