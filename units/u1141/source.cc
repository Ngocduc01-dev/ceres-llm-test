// u1141 – ceres::internal::SparseSchurComplementSolver::InitStorage
// Trích từ internal/ceres/schur_complement_solver.cc, dòng 223–288 (chỉ để xem, không compile)

void SparseSchurComplementSolver::InitStorage(
    const CompressedRowBlockStructure* bs) {
  const int num_eliminate_blocks = options().elimination_groups[0];
  const int num_col_blocks = bs->cols.size();
  const int num_row_blocks = bs->rows.size();

  blocks_ = Tail(bs->cols, num_col_blocks - num_eliminate_blocks);

  std::set<std::pair<int, int>> block_pairs;
  for (int i = 0; i < blocks_.size(); ++i) {
    block_pairs.emplace(i, i);
  }

  int r = 0;
  while (r < num_row_blocks) {
    int e_block_id = bs->rows[r].cells.front().block_id;
    if (e_block_id >= num_eliminate_blocks) {
      break;
    }
    std::vector<int> f_blocks;

    // Add to the chunk until the first block in the row is
    // different than the one in the first row for the chunk.
    for (; r < num_row_blocks; ++r) {
      const CompressedRow& row = bs->rows[r];
      if (row.cells.front().block_id != e_block_id) {
        break;
      }

      // Iterate over the blocks in the row, ignoring the first
      // block since it is the one to be eliminated.
      for (int c = 1; c < row.cells.size(); ++c) {
        const Cell& cell = row.cells[c];
        f_blocks.push_back(cell.block_id - num_eliminate_blocks);
      }
    }

    sort(f_blocks.begin(), f_blocks.end());
    f_blocks.erase(unique(f_blocks.begin(), f_blocks.end()), f_blocks.end());
    for (int i = 0; i < f_blocks.size(); ++i) {
      for (int j = i + 1; j < f_blocks.size(); ++j) {
        block_pairs.emplace(f_blocks[i], f_blocks[j]);
      }
    }
  }

  // Remaining rows do not contribute to the chunks and directly go
  // into the schur complement via an outer product.
  for (; r < num_row_blocks; ++r) {
    const CompressedRow& row = bs->rows[r];
    CHECK_GE(row.cells.front().block_id, num_eliminate_blocks);
    for (int i = 0; i < row.cells.size(); ++i) {
      int r_block1_id = row.cells[i].block_id - num_eliminate_blocks;
      for (const auto& cell : row.cells) {
        int r_block2_id = cell.block_id - num_eliminate_blocks;
        if (r_block1_id <= r_block2_id) {
          block_pairs.emplace(r_block1_id, r_block2_id);
        }
      }
    }
  }

  set_lhs(std::make_unique<BlockRandomAccessSparseMatrix>(
      blocks_, block_pairs, options().context, options().num_threads));
  ResizeRhs(lhs()->num_rows());
}
