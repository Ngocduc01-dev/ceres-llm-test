// u0633 – ceres::internal::operator<=
// Trích từ include/ceres/internal/fixed_array.h, dòng 328–330 (chỉ để xem, không compile)

  friend bool operator<=(const FixedArray& lhs, const FixedArray& rhs) {
    return !(rhs < lhs);
  }
