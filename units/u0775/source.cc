// u0775 – ceres::internal::ComputeVisibility
// Trích từ internal/ceres/visibility.cc, dòng 49–74 (chỉ để xem, không compile)

void ComputeVisibility(const CompressedRowBlockStructure& block_structure,
                       const int num_eliminate_blocks,
                       std::vector<std::set<int>>* visibility) {
  CHECK(visibility != nullptr);

  // Clear the visibility vector and resize it to hold a
  // vector for each camera.
  visibility->resize(0);
  visibility->resize(block_structure.cols.size() - num_eliminate_blocks);

  for (const auto& row : block_structure.rows) {
    const std::vector<Cell>& cells = row.cells;
    int block_id = cells[0].block_id;
    // If the first block is not an e_block, then skip this row block.
    if (block_id >= num_eliminate_blocks) {
      continue;
    }

    for (int j = 1; j < cells.size(); ++j) {
      int camera_block_id = cells[j].block_id - num_eliminate_blocks;
      DCHECK_GE(camera_block_id, 0);
      DCHECK_LT(camera_block_id, visibility->size());
      (*visibility)[camera_block_id].insert(block_id);
    }
  }
}
