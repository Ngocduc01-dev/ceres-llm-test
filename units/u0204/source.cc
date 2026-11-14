// u0204 – ceres::MatrixAdapter::operator()
// Trích từ include/ceres/rotation.h, dòng 299–301 (chỉ để xem, không compile)

  T& operator()(int r, int c) const {
    return pointer_[r * row_stride + c * col_stride];
  }
