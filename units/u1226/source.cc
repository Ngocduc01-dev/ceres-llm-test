// u1226 – ceres::internal::PartitionedMatrixView::CreateBlockDiagonalMatrixLayout
// Trích từ internal/ceres/partitioned_matrix_view_impl.h, dòng 382–418 (chỉ để xem, không compile)

template <int kRowBlockSize, int kEBlockSize, int kFBlockSize>
std::unique_ptr<BlockSparseMatrix>
PartitionedMatrixView<kRowBlockSize, kEBlockSize, kFBlockSize>::
    CreateBlockDiagonalMatrixLayout(int start_col_block,
                                    int end_col_block) const {
  const CompressedRowBlockStructure* bs = matrix_.block_structure();
  auto* block_diagonal_structure = new CompressedRowBlockStructure;

  int block_position = 0;
  int diagonal_cell_position = 0;

  // Iterate over the column blocks, creating a new diagonal block for
  // each column block.
  for (int c = start_col_block; c < end_col_block; ++c) {
    const Block& block = bs->cols[c];
    block_diagonal_structure->cols.emplace_back();
    Block& diagonal_block = block_diagonal_structure->cols.back();
    diagonal_block.size = block.size;
    diagonal_block.position = block_position;

    block_diagonal_structure->rows.emplace_back();
    CompressedRow& row = block_diagonal_structure->rows.back();
    row.block = diagonal_block;

    row.cells.emplace_back();
    Cell& cell = row.cells.back();
    cell.block_id = c - start_col_block;
    cell.position = diagonal_cell_position;

    block_position += block.size;
    diagonal_cell_position += block.size * block.size;
  }

  // Build a BlockSparseMatrix with the just computed block
  // structure.
  return std::make_unique<BlockSparseMatrix>(block_diagonal_structure);
}
