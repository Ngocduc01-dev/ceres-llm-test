// u1239 – ceres::internal::FixedArray::Storage::Storage
// Trích từ include/ceres/internal/fixed_array.h, dòng 416–417 (chỉ để xem, không compile)

    Storage(size_type n, const allocator_type& a)
        : size_alloc_(n, a), data_(InitializeData()) {}
