// u0786 – ceres::internal::FixedArray::AsValueType
// Trích từ include/ceres/internal/fixed_array.h, dòng 370–372 (chỉ để xem, không compile)

  static pointer AsValueType(StorageElementWrapper<value_type>* ptr) {
    return std::addressof(ptr->array);
  }
