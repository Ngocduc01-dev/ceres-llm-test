// u0044 – ceres::internal::FixedArray::rend
// Trích từ include/ceres/internal/fixed_array.h, dòng 295–297 (chỉ để xem, không compile)

  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }
