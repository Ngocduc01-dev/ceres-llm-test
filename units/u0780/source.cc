// u0780 – ceres::internal::SchurEliminator::Init
// Trích từ internal/ceres/schur_eliminator_impl.h, dòng 79–174 (chỉ để xem, không compile)

template <int kRowBlockSize, int kEBlockSize, int kFBlockSize>
void SchurEliminator<kRowBlockSize, kEBlockSize, kFBlockSize>::Init(
    int num_eliminate_blocks,
    bool assume_full_rank_ete,
    const CompressedRowBlockStructure* bs) {
  CHECK_GT(num_eliminate_blocks, 0)
      << "SchurComplementSolver cannot be initialized with "
      << "num_eliminate_blocks = 0.";

  num_eliminate_blocks_ = num_eliminate_blocks;
  assume_full_rank_ete_ = assume_full_rank_ete;

  const int num_col_blocks = bs->cols.size();
  const int num_row_blocks = bs->rows.size();

  buffer_size_ = 1;
  chunks_.clear();
  lhs_row_layout_.clear();

  int lhs_num_rows = 0;
  // Add a map object for each block in the reduced linear system
  // and build the row/column block structure of the reduced linear
  // system.
  lhs_row_layout_.resize(num_col_blocks - num_eliminate_blocks_);
  for (int i = num_eliminate_blocks_; i < num_col_blocks; ++i) {
    lhs_row_layout_[i - num_eliminate_blocks_] = lhs_num_rows;
    lhs_num_rows += bs->cols[i].size;
  }

  // TODO(sameeragarwal): Now that we may have subset block structure,
  // we need to make sure that we account for the fact that some
  // point blocks only have a "diagonal" row and nothing more.
  //
  // This likely requires a slightly different algorithm, which works
  // off of the number of elimination blocks.

  int r = 0;
  // Iterate over the row blocks of A, and detect the chunks. The
  // matrix should already have been ordered so that all rows
  // containing the same y block are vertically contiguous. Along
  // the way also compute the amount of space each chunk will need
  // to perform the elimination.
  while (r < num_row_blocks) {
    const int chunk_block_id = bs->rows[r].cells.front().block_id;
    if (chunk_block_id >= num_eliminate_blocks_) {
      break;
    }

    chunks_.push_back(Chunk(r));
    Chunk& chunk = chunks_.back();
    int buffer_size = 0;
    const int e_block_size = bs->cols[chunk_block_id].size;

    // Add to the chunk until the first block in the row is
    // different than the one in the first row for the chunk.
    while (r + chunk.size < num_row_blocks) {
      const CompressedRow& row = bs->rows[r + chunk.size];
      if (row.cells.front().block_id != chunk_block_id) {
        break;
      }

      // Iterate over the blocks in the row, ignoring the first
      // block since it is the one to be eliminated.
      for (int c = 1; c < row.cells.size(); ++c) {
        const Cell& cell = row.cells[c];
        if (InsertIfNotPresent(
                &(chunk.buffer_layout), cell.block_id, buffer_size)) {
          buffer_size += e_block_size * bs->cols[cell.block_id].size;
        }
      }

      buffer_size_ = std::max(buffer_size, buffer_size_);
      ++chunk.size;
    }

    CHECK_GT(chunk.size, 0);  // This check will need to be resolved.
    r += chunk.size;
  }
  const Chunk& chunk = chunks_.back();

  uneliminated_row_begins_ = chunk.start + chunk.size;

  buffer_ = std::make_unique<double[]>(buffer_size_ * num_threads_);

  // chunk_outer_product_buffer_ only needs to store e_block_size *
  // f_block_size, which is always less than buffer_size_, so we just
  // allocate buffer_size_ per thread.
  chunk_outer_product_buffer_ =
      std::make_unique<double[]>(buffer_size_ * num_threads_);

  STLDeleteElements(&rhs_locks_);
  rhs_locks_.resize(num_col_blocks - num_eliminate_blocks_);
  for (int i = 0; i < num_col_blocks - num_eliminate_blocks_; ++i) {
    rhs_locks_[i] = new std::mutex;
  }
}
