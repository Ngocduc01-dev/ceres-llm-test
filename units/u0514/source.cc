// u0514 – ceres::Grid1D::GetValue
// Trích từ include/ceres/cubic_interpolation.h, dòng 193–204 (chỉ để xem, không compile)

  EIGEN_STRONG_INLINE void GetValue(const int n, double* f) const {
    const int idx = (std::min)((std::max)(begin_, n), end_ - 1) - begin_;
    if (kInterleaved) {
      for (int i = 0; i < kDataDimension; ++i) {
        f[i] = static_cast<double>(data_[kDataDimension * idx + i]);
      }
    } else {
      for (int i = 0; i < kDataDimension; ++i) {
        f[i] = static_cast<double>(data_[i * num_values_ + idx]);
      }
    }
  }
