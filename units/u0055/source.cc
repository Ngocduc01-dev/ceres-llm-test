// u0055 – ceres::internal::FixedArray::Storage::alloc
// Trích từ include/ceres/internal/fixed_array.h, dòng 430–430 (chỉ để xem, không compile)

    allocator_type& alloc() { return std::get<1>(size_alloc_); }
