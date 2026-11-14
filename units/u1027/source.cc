// u1027 – ceres::internal::FixedArray::operator[]
// Trích từ include/ceres/internal/fixed_array.h, dòng 221–224 (chỉ để xem, không compile)

  const_reference operator[](size_type i) const {
    DCHECK_LT(i, size());
    return data()[i];
  }
