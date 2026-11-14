// u0720 – ceres::internal::Tail
// Trích từ internal/ceres/block_structure.cc, dòng 46–60 (chỉ để xem, không compile)

std::vector<Block> Tail(const std::vector<Block>& blocks, int n) {
  CHECK_LE(n, blocks.size());
  std::vector<Block> tail;
  const int num_blocks = blocks.size();
  const int start = num_blocks - n;

  int position = 0;
  tail.reserve(n);
  for (int i = start; i < num_blocks; ++i) {
    tail.emplace_back(blocks[i].size, position);
    position += blocks[i].size;
  }

  return tail;
}
