// u0699 – ceres::internal::CellLessThan
// Trích từ internal/ceres/block_structure.cc, dòng 39–44 (chỉ để xem, không compile)

bool CellLessThan(const Cell& lhs, const Cell& rhs) {
  if (lhs.block_id == rhs.block_id) {
    return (lhs.position < rhs.position);
  }
  return (lhs.block_id < rhs.block_id);
}
