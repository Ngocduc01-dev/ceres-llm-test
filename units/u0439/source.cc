// u0439 – ceres::CubicInterpolator::Evaluate
// Trích từ include/ceres/cubic_interpolation.h, dòng 148–156 (chỉ để xem, không compile)

  template <typename JetT>
  void Evaluate(const JetT& x, JetT* f) const {
    double fx[Grid::DATA_DIMENSION], dfdx[Grid::DATA_DIMENSION];
    Evaluate(x.a, fx, dfdx);
    for (int i = 0; i < Grid::DATA_DIMENSION; ++i) {
      f[i].a = fx[i];
      f[i].v = dfdx[i] * x.v;
    }
  }
