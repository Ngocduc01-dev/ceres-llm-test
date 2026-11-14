// u0694 – ceres::CubicInterpolator::CubicInterpolator<Grid>
// Trích từ include/ceres/cubic_interpolation.h, dòng 126–131 (chỉ để xem, không compile)

  explicit CubicInterpolator(const Grid& grid) : grid_(grid) {
    // The + casts the enum into an int before doing the
    // comparison. It is needed to prevent
    // "-Wunnamed-type-template-args" related errors.
    CHECK_GE(+Grid::DATA_DIMENSION, 1);
  }
