// u0695 – ceres::BiCubicInterpolator::BiCubicInterpolator<Grid>
// Trích từ include/ceres/cubic_interpolation.h, dòng 254–259 (chỉ để xem, không compile)

  explicit BiCubicInterpolator(const Grid& grid) : grid_(grid) {
    // The + casts the enum into an int before doing the
    // comparison. It is needed to prevent
    // "-Wunnamed-type-template-args" related errors.
    CHECK_GE(+Grid::DATA_DIMENSION, 1);
  }
