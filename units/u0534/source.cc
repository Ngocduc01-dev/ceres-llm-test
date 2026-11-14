// u0534 – ceres::Grid2D::GetValue
// Trích từ include/ceres/cubic_interpolation.h, dòng 403–421 (chỉ để xem, không compile)

  EIGEN_STRONG_INLINE void GetValue(const int r, const int c, double* f) const {
    const int row_idx =
        (std::min)((std::max)(row_begin_, r), row_end_ - 1) - row_begin_;
    const int col_idx =
        (std::min)((std::max)(col_begin_, c), col_end_ - 1) - col_begin_;

    const int n = (kRowMajor) ? num_cols_ * row_idx + col_idx
                              : num_rows_ * col_idx + row_idx;

    if (kInterleaved) {
      for (int i = 0; i < kDataDimension; ++i) {
        f[i] = static_cast<double>(data_[kDataDimension * n + i]);
      }
    } else {
      for (int i = 0; i < kDataDimension; ++i) {
        f[i] = static_cast<double>(data_[i * num_values_ + n]);
      }
    }
  }
