// u0515 – ceres::Grid2D::Grid2D<T, kDataDimension, kRowMajor, kInterleaved>
// Trích từ include/ceres/cubic_interpolation.h, dòng 385–401 (chỉ để xem, không compile)

  Grid2D(const T* data,
         const int row_begin,
         const int row_end,
         const int col_begin,
         const int col_end)
      : data_(data),
        row_begin_(row_begin),
        row_end_(row_end),
        col_begin_(col_begin),
        col_end_(col_end),
        num_rows_(row_end - row_begin),
        num_cols_(col_end - col_begin),
        num_values_(num_rows_ * num_cols_) {
    CHECK_GE(kDataDimension, 1);
    CHECK_LT(row_begin, row_end);
    CHECK_LT(col_begin, col_end);
  }
