// u1026 – ceres::internal::FixedArray::operator[]
// Trích từ include/ceres/internal/fixed_array.h, dòng 213–216 (chỉ để xem, không compile)

  reference operator[](size_type i) {
    DCHECK_LT(i, size());
    return data()[i];
  }
