// u0700 – ceres::internal::SumSquaredSizes
// Trích từ internal/ceres/block_structure.cc, dòng 62–68 (chỉ để xem, không compile)

int SumSquaredSizes(const std::vector<Block>& blocks) {
  int sum = 0;
  for (const auto& b : blocks) {
    sum += b.size * b.size;
  }
  return sum;
}
