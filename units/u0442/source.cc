// u0442 – ceres::BiCubicInterpolator::Evaluate
// Trích từ include/ceres/cubic_interpolation.h, dòng 334–344 (chỉ để xem, không compile)

  template <typename JetT>
  void Evaluate(const JetT& r, const JetT& c, JetT* f) const {
    double frc[Grid::DATA_DIMENSION];
    double dfdr[Grid::DATA_DIMENSION];
    double dfdc[Grid::DATA_DIMENSION];
    Evaluate(r.a, c.a, frc, dfdr, dfdc);
    for (int i = 0; i < Grid::DATA_DIMENSION; ++i) {
      f[i].a = frc[i];
      f[i].v = dfdr[i] * r.v + dfdc[i] * c.v;
    }
  }
