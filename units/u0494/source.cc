// u0494 – ceres::CubicHermiteSpline
// Trích từ include/ceres/cubic_interpolation.h, dòng 64–90 (chỉ để xem, không compile)

template <int kDataDimension>
void CubicHermiteSpline(const Eigen::Matrix<double, kDataDimension, 1>& p0,
                        const Eigen::Matrix<double, kDataDimension, 1>& p1,
                        const Eigen::Matrix<double, kDataDimension, 1>& p2,
                        const Eigen::Matrix<double, kDataDimension, 1>& p3,
                        const double x,
                        double* f,
                        double* dfdx) {
  using VType = Eigen::Matrix<double, kDataDimension, 1>;
  const VType a = 0.5 * (-p0 + 3.0 * p1 - 3.0 * p2 + p3);
  const VType b = 0.5 * (2.0 * p0 - 5.0 * p1 + 4.0 * p2 - p3);
  const VType c = 0.5 * (-p0 + p2);
  const VType d = p1;

  // Use Horner's rule to evaluate the function value and its
  // derivative.

  // f = ax^3 + bx^2 + cx + d
  if (f != nullptr) {
    Eigen::Map<VType>(f, kDataDimension) = d + x * (c + x * (b + x * a));
  }

  // dfdx = 3ax^2 + 2bx + c
  if (dfdx != nullptr) {
    Eigen::Map<VType>(dfdx, kDataDimension) = c + x * (2.0 * b + 3.0 * a * x);
  }
}
