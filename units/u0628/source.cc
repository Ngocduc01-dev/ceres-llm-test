// u0628 – ceres::internal::FixedArray::FixedArray<T, N, A>
// Trích từ include/ceres/internal/fixed_array.h, dòng 148–150 (chỉ để xem, không compile)

  FixedArray(std::initializer_list<value_type> init_list,
             const allocator_type& a = allocator_type())
      : FixedArray(init_list.begin(), init_list.end(), a) {}
