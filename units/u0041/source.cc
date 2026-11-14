// u0041 – ceres::internal::FixedArray::rbegin
// Trích từ include/ceres/internal/fixed_array.h, dòng 279–281 (chỉ để xem, không compile)

  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }
