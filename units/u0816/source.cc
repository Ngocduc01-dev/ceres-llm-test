// u0816 – ceres::internal::VisibilityBasedPreconditioner::ComputeBlockPairsInPreconditioner
// Trích từ internal/ceres/visibility_based_preconditioner.cc, dòng 220–299 (chỉ để xem, không compile)

void VisibilityBasedPreconditioner::ComputeBlockPairsInPreconditioner(
    const CompressedRowBlockStructure& bs) {
  block_pairs_.clear();
  for (int i = 0; i < num_blocks_; ++i) {
    block_pairs_.insert(std::make_pair(i, i));
  }

  int r = 0;
  const int num_row_blocks = bs.rows.size();
  const int num_eliminate_blocks = options_.elimination_groups[0];

  // Iterate over each row of the matrix. The block structure of the
  // matrix is assumed to be sorted in order of the e_blocks/point
  // blocks. Thus all row blocks containing an e_block/point occur
  // contiguously. Further, if present, an e_block is always the first
  // parameter block in each row block.  These structural assumptions
  // are common to all Schur complement based solvers in Ceres.
  //
  // For each e_block/point block we identify the set of cameras
  // seeing it. The cross product of this set with itself is the set
  // of non-zero cells contributed by this e_block.
  //
  // The time complexity of this is O(nm^2) where, n is the number of
  // 3d points and m is the maximum number of cameras seeing any
  // point, which for most scenes is a fairly small number.
  while (r < num_row_blocks) {
    int e_block_id = bs.rows[r].cells.front().block_id;
    if (e_block_id >= num_eliminate_blocks) {
      // Skip the rows whose first block is an f_block.
      break;
    }

    std::set<int> f_blocks;
    for (; r < num_row_blocks; ++r) {
      const CompressedRow& row = bs.rows[r];
      if (row.cells.front().block_id != e_block_id) {
        break;
      }

      // Iterate over the blocks in the row, ignoring the first block
      // since it is the one to be eliminated and adding the rest to
      // the list of f_blocks associated with this e_block.
      for (int c = 1; c < row.cells.size(); ++c) {
        const Cell& cell = row.cells[c];
        const int f_block_id = cell.block_id - num_eliminate_blocks;
        CHECK_GE(f_block_id, 0);
        f_blocks.insert(f_block_id);
      }
    }

    for (auto block1 = f_blocks.begin(); block1 != f_blocks.end(); ++block1) {
      auto block2 = block1;
      ++block2;
      for (; block2 != f_blocks.end(); ++block2) {
        if (IsBlockPairInPreconditioner(*block1, *block2)) {
          block_pairs_.emplace(*block1, *block2);
        }
      }
    }
  }

  // The remaining rows which do not contain any e_blocks.
  for (; r < num_row_blocks; ++r) {
    const CompressedRow& row = bs.rows[r];
    CHECK_GE(row.cells.front().block_id, num_eliminate_blocks);
    for (int i = 0; i < row.cells.size(); ++i) {
      const int block1 = row.cells[i].block_id - num_eliminate_blocks;
      for (const auto& cell : row.cells) {
        const int block2 = cell.block_id - num_eliminate_blocks;
        if (block1 <= block2) {
          if (IsBlockPairInPreconditioner(block1, block2)) {
            block_pairs_.insert(std::make_pair(block1, block2));
          }
        }
      }
    }
  }

  VLOG(1) << "Block pair stats: " << block_pairs_.size();
}
