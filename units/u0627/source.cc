// u0627 – ceres::internal::FixedArray::FixedArray<T, N, A>
// Trích từ include/ceres/internal/fixed_array.h, dòng 125–128 (chỉ để xem, không compile)

  FixedArray(FixedArray&& other, const allocator_type& a = allocator_type())
      : FixedArray(std::make_move_iterator(other.begin()),
                   std::make_move_iterator(other.end()),
                   a) {}
