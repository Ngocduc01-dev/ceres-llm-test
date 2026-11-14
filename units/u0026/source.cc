// u0026 – ceres::internal::FixedArray::FixedArray<T, N, A>
// Trích từ include/ceres/internal/fixed_array.h, dòng 140–145 (chỉ để xem, không compile)

  FixedArray(size_type n,
             const value_type& val,
             const allocator_type& a = allocator_type())
      : storage_(n, a) {
    ConstructRange(storage_.alloc(), storage_.begin(), storage_.end(), val);
  }
