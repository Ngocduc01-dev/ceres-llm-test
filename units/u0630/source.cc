// u0630 – ceres::internal::operator!=
// Trích từ include/ceres/internal/fixed_array.h, dòng 315–317 (chỉ để xem, không compile)

  friend bool operator!=(const FixedArray& lhs, const FixedArray& rhs) {
    return !(lhs == rhs);
  }
