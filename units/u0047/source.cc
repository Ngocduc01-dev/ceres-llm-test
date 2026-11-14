// u0047 – ceres::internal::FixedArray::NonEmptyInlinedStorage::data
// Trích từ include/ceres/internal/fixed_array.h, dòng 379–379 (chỉ để xem, không compile)

    StorageElement* data() { return reinterpret_cast<StorageElement*>(buff_); }
