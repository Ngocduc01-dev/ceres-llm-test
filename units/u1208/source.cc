// u1208 – ceres::internal::CompressedRowSparseMatrix::CreateBlockDiagonalMatrix
// Trích từ internal/ceres/compressed_row_sparse_matrix.cc, dòng 559–598 (chỉ để xem, không compile)

std::unique_ptr<CompressedRowSparseMatrix>
CompressedRowSparseMatrix::CreateBlockDiagonalMatrix(
    const double* diagonal, const std::vector<Block>& blocks) {
  const int num_rows = NumScalarEntries(blocks);
  int num_nonzeros = 0;
  for (auto& block : blocks) {
    num_nonzeros += block.size * block.size;
  }

  auto matrix = std::make_unique<CompressedRowSparseMatrix>(
      num_rows, num_rows, num_nonzeros);

  int* rows = matrix->mutable_rows();
  int* cols = matrix->mutable_cols();
  double* values = matrix->mutable_values();
  std::fill(values, values + num_nonzeros, 0.0);

  int idx_cursor = 0;
  int col_cursor = 0;
  for (auto& block : blocks) {
    for (int r = 0; r < block.size; ++r) {
      *(rows++) = idx_cursor;
      if (diagonal != nullptr) {
        values[idx_cursor + r] = diagonal[col_cursor + r];
      }
      for (int c = 0; c < block.size; ++c, ++idx_cursor) {
        *(cols++) = col_cursor + c;
      }
    }
    col_cursor += block.size;
  }
  *rows = idx_cursor;

  *matrix->mutable_row_blocks() = blocks;
  *matrix->mutable_col_blocks() = blocks;

  CHECK_EQ(idx_cursor, num_nonzeros);
  CHECK_EQ(col_cursor, num_rows);
  return matrix;
}
