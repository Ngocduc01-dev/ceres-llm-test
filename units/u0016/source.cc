// u0016 – ceres::CubicInterpolator::Evaluate
// Trích từ include/ceres/cubic_interpolation.h, dòng 133–141 (chỉ để xem, không compile)

  void Evaluate(double x, double* f, double* dfdx) const {
    const int n = std::floor(x);
    Eigen::Matrix<double, Grid::DATA_DIMENSION, 1> p0, p1, p2, p3;
    grid_.GetValue(n - 1, p0.data());
    grid_.GetValue(n, p1.data());
    grid_.GetValue(n + 1, p2.data());
    grid_.GetValue(n + 2, p3.data());
    CubicHermiteSpline<Grid::DATA_DIMENSION>(p0, p1, p2, p3, x - n, f, dfdx);
  }
