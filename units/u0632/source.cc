// u0632 – ceres::internal::operator>
// Trích từ include/ceres/internal/fixed_array.h, dòng 324–326 (chỉ để xem, không compile)

  friend bool operator>(const FixedArray& lhs, const FixedArray& rhs) {
    return rhs < lhs;
  }
