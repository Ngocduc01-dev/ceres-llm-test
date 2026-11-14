// u0626 – ceres::internal::FixedArray::FixedArray<T, N, A>
// Trích từ include/ceres/internal/fixed_array.h, dòng 121–123 (chỉ để xem, không compile)

  FixedArray(const FixedArray& other,
             const allocator_type& a = allocator_type())
      : FixedArray(other.begin(), other.end(), a) {}
