// u0562 – ceres::internal::FixedArray::DefaultConstructorIsNonTrivial
// Trích từ include/ceres/internal/fixed_array.h, dòng 99–101 (chỉ để xem, không compile)

  static constexpr bool DefaultConstructorIsNonTrivial() {
    return !std::is_trivially_default_constructible<StorageElement>::value;
  }
