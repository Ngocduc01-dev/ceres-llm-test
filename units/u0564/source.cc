// u0564 – ceres::internal::FixedArray::Storage::UsingInlinedStorage
// Trích từ include/ceres/internal/fixed_array.h, dòng 433–435 (chỉ để xem, không compile)

    static bool UsingInlinedStorage(size_type n) {
      return n <= inline_elements;
    }
