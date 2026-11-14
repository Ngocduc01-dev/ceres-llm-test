// u0631 – ceres::internal::operator<
// Trích từ include/ceres/internal/fixed_array.h, dòng 319–322 (chỉ để xem, không compile)

  friend bool operator<(const FixedArray& lhs, const FixedArray& rhs) {
    return std::lexicographical_compare(
        lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
  }
