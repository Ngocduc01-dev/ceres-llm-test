// u0701 – ceres::internal::operator==
// Trích từ internal/ceres/block_structure.h, dòng 62–64 (chỉ để xem, không compile)

inline bool operator==(const Block& left, const Block& right) noexcept {
  return (left.size == right.size) && (left.position == right.position);
}
