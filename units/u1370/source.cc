// u1370 – ceres::internal::CompressedRowSparseMatrix::CreateRandomMatrix
// Trích từ internal/ceres/compressed_row_sparse_matrix.cc, dòng 640–767 (chỉ để xem, không compile)

std::unique_ptr<CompressedRowSparseMatrix>
CompressedRowSparseMatrix::CreateRandomMatrix(
    CompressedRowSparseMatrix::RandomMatrixOptions options,
    std::mt19937& prng) {
  CHECK_GT(options.num_row_blocks, 0);
  CHECK_GT(options.min_row_block_size, 0);
  CHECK_GT(options.max_row_block_size, 0);
  CHECK_LE(options.min_row_block_size, options.max_row_block_size);

  if (options.storage_type == StorageType::UNSYMMETRIC) {
    CHECK_GT(options.num_col_blocks, 0);
    CHECK_GT(options.min_col_block_size, 0);
    CHECK_GT(options.max_col_block_size, 0);
    CHECK_LE(options.min_col_block_size, options.max_col_block_size);
  } else {
    // Symmetric matrices (LOWER_TRIANGULAR or UPPER_TRIANGULAR);
    options.num_col_blocks = options.num_row_blocks;
    options.min_col_block_size = options.min_row_block_size;
    options.max_col_block_size = options.max_row_block_size;
  }

  CHECK_GT(options.block_density, 0.0);
  CHECK_LE(options.block_density, 1.0);

  std::vector<Block> row_blocks;
  row_blocks.reserve(options.num_row_blocks);
  std::vector<Block> col_blocks;
  col_blocks.reserve(options.num_col_blocks);

  std::uniform_int_distribution<int> col_distribution(
      options.min_col_block_size, options.max_col_block_size);
  std::uniform_int_distribution<int> row_distribution(
      options.min_row_block_size, options.max_row_block_size);
  std::uniform_real_distribution<double> uniform01(0.0, 1.0);
  std::normal_distribution<double> standard_normal_distribution;

  // Generate the row block structure.
  int row_pos = 0;
  for (int i = 0; i < options.num_row_blocks; ++i) {
    // Generate a random integer in [min_row_block_size, max_row_block_size]
    row_blocks.emplace_back(row_distribution(prng), row_pos);
    row_pos += row_blocks.back().size;
  }

  if (options.storage_type == StorageType::UNSYMMETRIC) {
    // Generate the col block structure.
    int col_pos = 0;
    for (int i = 0; i < options.num_col_blocks; ++i) {
      // Generate a random integer in [min_col_block_size, max_col_block_size]
      col_blocks.emplace_back(col_distribution(prng), col_pos);
      col_pos += col_blocks.back().size;
    }
  } else {
    // Symmetric matrices (LOWER_TRIANGULAR or UPPER_TRIANGULAR);
    col_blocks = row_blocks;
  }

  std::vector<int> tsm_rows;
  std::vector<int> tsm_cols;
  std::vector<double> tsm_values;

  // For ease of construction, we are going to generate the
  // CompressedRowSparseMatrix by generating it as a
  // TripletSparseMatrix and then converting it to a
  // CompressedRowSparseMatrix.

  // It is possible that the random matrix is empty which is likely
  // not what the user wants, so do the matrix generation till we have
  // at least one non-zero entry.
  while (tsm_values.empty()) {
    tsm_rows.clear();
    tsm_cols.clear();
    tsm_values.clear();

    int row_block_begin = 0;
    for (int r = 0; r < options.num_row_blocks; ++r) {
      int col_block_begin = 0;
      for (int c = 0; c < options.num_col_blocks; ++c) {
        if (((options.storage_type == StorageType::UPPER_TRIANGULAR) &&
             (r > c)) ||
            ((options.storage_type == StorageType::LOWER_TRIANGULAR) &&
             (r < c))) {
          col_block_begin += col_blocks[c].size;
          continue;
        }

        // Randomly determine if this block is present or not.
        if (uniform01(prng) <= options.block_density) {
          auto randn = [&standard_normal_distribution, &prng] {
            return standard_normal_distribution(prng);
          };
          // If the matrix is symmetric, then we take care to generate
          // symmetric diagonal blocks.
          if (options.storage_type == StorageType::UNSYMMETRIC || r != c) {
            AddRandomBlock(row_blocks[r].size,
                           col_blocks[c].size,
                           row_block_begin,
                           col_block_begin,
                           randn,
                           &tsm_rows,
                           &tsm_cols,
                           &tsm_values);
          } else {
            AddSymmetricRandomBlock(row_blocks[r].size,
                                    row_block_begin,
                                    randn,
                                    &tsm_rows,
                                    &tsm_cols,
                                    &tsm_values);
          }
        }
        col_block_begin += col_blocks[c].size;
      }
      row_block_begin += row_blocks[r].size;
    }
  }

  const int num_rows = NumScalarEntries(row_blocks);
  const int num_cols = NumScalarEntries(col_blocks);
  const bool kDoNotTranspose = false;
  auto matrix = CompressedRowSparseMatrix::FromTripletSparseMatrix(
      TripletSparseMatrix(num_rows, num_cols, tsm_rows, tsm_cols, tsm_values),
      kDoNotTranspose);
  (*matrix->mutable_row_blocks()) = row_blocks;
  (*matrix->mutable_col_blocks()) = col_blocks;
  matrix->set_storage_type(options.storage_type);
  return matrix;
}
