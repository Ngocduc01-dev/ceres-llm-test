// u0441 – ceres::BiCubicInterpolator::Evaluate
// Trích từ include/ceres/cubic_interpolation.h, dòng 264–325 (chỉ để xem, không compile)

  void Evaluate(
      double r, double c, double* f, double* dfdr, double* dfdc) const {
    // BiCubic interpolation requires 16 values around the point being
    // evaluated.  We will use pij, to indicate the elements of the
    // 4x4 grid of values.
    //
    //          col
    //      p00 p01 p02 p03
    // row  p10 p11 p12 p13
    //      p20 p21 p22 p23
    //      p30 p31 p32 p33
    //
    // The point (r,c) being evaluated is assumed to lie in the square
    // defined by p11, p12, p22 and p21.

    const int row = std::floor(r);
    const int col = std::floor(c);

    Eigen::Matrix<double, Grid::DATA_DIMENSION, 1> p0, p1, p2, p3;

    // Interpolate along each of the four rows, evaluating the function
    // value and the horizontal derivative in each row.
    Eigen::Matrix<double, Grid::DATA_DIMENSION, 1> f0, f1, f2, f3;
    Eigen::Matrix<double, Grid::DATA_DIMENSION, 1> df0dc, df1dc, df2dc, df3dc;

    grid_.GetValue(row - 1, col - 1, p0.data());
    grid_.GetValue(row - 1, col, p1.data());
    grid_.GetValue(row - 1, col + 1, p2.data());
    grid_.GetValue(row - 1, col + 2, p3.data());
    CubicHermiteSpline<Grid::DATA_DIMENSION>(
        p0, p1, p2, p3, c - col, f0.data(), df0dc.data());

    grid_.GetValue(row, col - 1, p0.data());
    grid_.GetValue(row, col, p1.data());
    grid_.GetValue(row, col + 1, p2.data());
    grid_.GetValue(row, col + 2, p3.data());
    CubicHermiteSpline<Grid::DATA_DIMENSION>(
        p0, p1, p2, p3, c - col, f1.data(), df1dc.data());

    grid_.GetValue(row + 1, col - 1, p0.data());
    grid_.GetValue(row + 1, col, p1.data());
    grid_.GetValue(row + 1, col + 1, p2.data());
    grid_.GetValue(row + 1, col + 2, p3.data());
    CubicHermiteSpline<Grid::DATA_DIMENSION>(
        p0, p1, p2, p3, c - col, f2.data(), df2dc.data());

    grid_.GetValue(row + 2, col - 1, p0.data());
    grid_.GetValue(row + 2, col, p1.data());
    grid_.GetValue(row + 2, col + 1, p2.data());
    grid_.GetValue(row + 2, col + 2, p3.data());
    CubicHermiteSpline<Grid::DATA_DIMENSION>(
        p0, p1, p2, p3, c - col, f3.data(), df3dc.data());

    // Interpolate vertically the interpolated value from each row and
    // compute the derivative along the columns.
    CubicHermiteSpline<Grid::DATA_DIMENSION>(f0, f1, f2, f3, r - row, f, dfdr);
    if (dfdc != nullptr) {
      // Interpolate vertically the derivative along the columns.
      CubicHermiteSpline<Grid::DATA_DIMENSION>(
          df0dc, df1dc, df2dc, df3dc, r - row, dfdc, nullptr);
    }
  }
