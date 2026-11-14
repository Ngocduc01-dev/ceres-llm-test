// u0029 – ceres::internal::FixedArray::max_size
// Trích từ include/ceres/internal/fixed_array.h, dòng 184–186 (chỉ để xem, không compile)

  constexpr size_type max_size() const {
    return (std::numeric_limits<difference_type>::max)() / sizeof(value_type);
  }
