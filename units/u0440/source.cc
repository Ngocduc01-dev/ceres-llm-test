// u0440 – ceres::Grid1D::Grid1D<T, kDataDimension, kInterleaved>
// Trích từ include/ceres/cubic_interpolation.h, dòng 188–191 (chỉ để xem, không compile)

  Grid1D(const T* data, const int begin, const int end)
      : data_(data), begin_(begin), end_(end), num_values_(end - begin) {
    CHECK_LT(begin, end);
  }
