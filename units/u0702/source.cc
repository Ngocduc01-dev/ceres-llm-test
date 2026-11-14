// u0702 – ceres::internal::NumScalarEntries
// Trích từ internal/ceres/block_structure.h, dòng 184–191 (chỉ để xem, không compile)

inline int NumScalarEntries(const std::vector<Block>& blocks) {
  if (blocks.empty()) {
    return 0;
  }

  auto& block = blocks.back();
  return block.position + block.size;
}
