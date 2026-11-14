// u0027 – ceres::internal::FixedArray::FixedArray<T, N, A>
// Trích từ include/ceres/internal/fixed_array.h, dòng 155–161 (chỉ để xem, không compile)

  template <typename Iterator, EnableIfForwardIterator<Iterator>* = nullptr>
  FixedArray(Iterator first,
             Iterator last,
             const allocator_type& a = allocator_type())
      : storage_(std::distance(first, last), a) {
    CopyRange(storage_.alloc(), storage_.begin(), first, last);
  }
