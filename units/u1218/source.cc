// u1218 – ceres::internal::BlockSparseMatrix::CreateRandomMatrix
// Trích từ internal/ceres/block_sparse_matrix.cc, dòng 711–781 (chỉ để xem, không compile)

std::unique_ptr<BlockSparseMatrix> BlockSparseMatrix::CreateRandomMatrix(
    const BlockSparseMatrix::RandomMatrixOptions& options,
    std::mt19937& prng,
    bool use_page_locked_memory) {
  CHECK_GT(options.num_row_blocks, 0);
  CHECK_GT(options.min_row_block_size, 0);
  CHECK_GT(options.max_row_block_size, 0);
  CHECK_LE(options.min_row_block_size, options.max_row_block_size);
  CHECK_GT(options.block_density, 0.0);
  CHECK_LE(options.block_density, 1.0);

  std::uniform_int_distribution<int> col_distribution(
      options.min_col_block_size, options.max_col_block_size);
  std::uniform_int_distribution<int> row_distribution(
      options.min_row_block_size, options.max_row_block_size);
  auto bs = std::make_unique<CompressedRowBlockStructure>();
  if (options.col_blocks.empty()) {
    CHECK_GT(options.num_col_blocks, 0);
    CHECK_GT(options.min_col_block_size, 0);
    CHECK_GT(options.max_col_block_size, 0);
    CHECK_LE(options.min_col_block_size, options.max_col_block_size);

    // Generate the col block structure.
    int col_block_position = 0;
    for (int i = 0; i < options.num_col_blocks; ++i) {
      const int col_block_size = col_distribution(prng);
      bs->cols.emplace_back(col_block_size, col_block_position);
      col_block_position += col_block_size;
    }
  } else {
    bs->cols = options.col_blocks;
  }

  bool matrix_has_blocks = false;
  std::uniform_real_distribution<double> uniform01(0.0, 1.0);
  while (!matrix_has_blocks) {
    VLOG(1) << "Clearing";
    bs->rows.clear();
    int row_block_position = 0;
    int value_position = 0;
    for (int r = 0; r < options.num_row_blocks; ++r) {
      const int row_block_size = row_distribution(prng);
      bs->rows.emplace_back();
      CompressedRow& row = bs->rows.back();
      row.block.size = row_block_size;
      row.block.position = row_block_position;
      row_block_position += row_block_size;
      for (int c = 0; c < bs->cols.size(); ++c) {
        if (uniform01(prng) > options.block_density) continue;

        row.cells.emplace_back();
        Cell& cell = row.cells.back();
        cell.block_id = c;
        cell.position = value_position;
        value_position += row_block_size * bs->cols[c].size;
        matrix_has_blocks = true;
      }
    }
  }

  auto matrix =
      std::make_unique<BlockSparseMatrix>(bs.release(), use_page_locked_memory);
  double* values = matrix->mutable_values();
  std::normal_distribution<double> standard_normal_distribution;
  std::generate_n(
      values, matrix->num_nonzeros(), [&standard_normal_distribution, &prng] {
        return standard_normal_distribution(prng);
      });

  return matrix;
}
