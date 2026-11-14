// u0774 – ceres::internal::SchurEliminatorForOneFBlock::Init
// Trích từ internal/ceres/schur_eliminator.h, dòng 386–428 (chỉ để xem, không compile)

  void Init(int num_eliminate_blocks,
            bool /*assume_full_rank_ete*/,
            const CompressedRowBlockStructure* bs) override {
    CHECK_GT(num_eliminate_blocks, 0)
        << "SchurComplementSolver cannot be initialized with "
        << "num_eliminate_blocks = 0.";
    CHECK_EQ(bs->cols.size() - num_eliminate_blocks, 1);

    num_eliminate_blocks_ = num_eliminate_blocks;
    const int num_row_blocks = bs->rows.size();
    chunks_.clear();
    int r = 0;
    // Iterate over the row blocks of A, and detect the chunks. The
    // matrix should already have been ordered so that all rows
    // containing the same y block are vertically contiguous.
    while (r < num_row_blocks) {
      const int e_block_id = bs->rows[r].cells.front().block_id;
      if (e_block_id >= num_eliminate_blocks_) {
        break;
      }

      chunks_.push_back(Chunk());
      Chunk& chunk = chunks_.back();
      chunk.num_rows = 0;
      chunk.start = r;
      // Add to the chunk until the first block in the row is
      // different than the one in the first row for the chunk.
      while (r + chunk.num_rows < num_row_blocks) {
        const CompressedRow& row = bs->rows[r + chunk.num_rows];
        if (row.cells.front().block_id != e_block_id) {
          break;
        }
        ++chunk.num_rows;
      }
      r += chunk.num_rows;
    }

    const Chunk& last_chunk = chunks_.back();
    uneliminated_row_begins_ = last_chunk.start + last_chunk.num_rows;
    e_t_e_inverse_matrices_.resize(kEBlockSize * kEBlockSize * chunks_.size());
    std::fill(
        e_t_e_inverse_matrices_.begin(), e_t_e_inverse_matrices_.end(), 0.0);
  }
