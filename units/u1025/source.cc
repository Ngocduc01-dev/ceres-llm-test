// u1025 – ceres::internal::FixedArray::FixedArray<T, N, A>
// Trích từ include/ceres/internal/fixed_array.h, dòng 132–137 (chỉ để xem, không compile)

  explicit FixedArray(size_type n, const allocator_type& a = allocator_type())
      : storage_(n, a) {
    if (DefaultConstructorIsNonTrivial()) {
      ConstructRange(storage_.alloc(), storage_.begin(), storage_.end());
    }
  }
