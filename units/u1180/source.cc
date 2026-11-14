// u1180 – ceres::internal::BlockSparseMatrix::CreateDiagonalMatrix
// Trích từ internal/ceres/block_sparse_matrix.cc, dòng 581–614 (chỉ để xem, không compile)

std::unique_ptr<BlockSparseMatrix> BlockSparseMatrix::CreateDiagonalMatrix(
    const double* diagonal, const std::vector<Block>& column_blocks) {
  // Create the block structure for the diagonal matrix.
  auto* bs = new CompressedRowBlockStructure();
  bs->cols = column_blocks;
  int position = 0;
  bs->rows.resize(column_blocks.size(), CompressedRow(1));
  for (int i = 0; i < column_blocks.size(); ++i) {
    CompressedRow& row = bs->rows[i];
    row.block = column_blocks[i];
    Cell& cell = row.cells[0];
    cell.block_id = i;
    cell.position = position;
    position += row.block.size * row.block.size;
  }

  // Create the BlockSparseMatrix with the given block structure.
  auto matrix = std::make_unique<BlockSparseMatrix>(bs);
  matrix->SetZero();

  // Fill the values array of the block sparse matrix.
  double* values = matrix->mutable_values();
  for (const auto& column_block : column_blocks) {
    const int size = column_block.size;
    for (int j = 0; j < size; ++j) {
      // (j + 1) * size is compact way of accessing the (j,j) entry.
      values[j * (size + 1)] = diagonal[j];
    }
    diagonal += size;
    values += size * size;
  }

  return matrix;
}
