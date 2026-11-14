// u1140 – ceres::internal::SchurEliminator::EBlockRowOuterProduct
// Trích từ internal/ceres/schur_eliminator_impl.h, dòng 664–714 (chỉ để xem, không compile)

template <int kRowBlockSize, int kEBlockSize, int kFBlockSize>
void SchurEliminator<kRowBlockSize, kEBlockSize, kFBlockSize>::
    EBlockRowOuterProduct(const BlockSparseMatrixData& A,
                          int row_block_index,
                          BlockRandomAccessMatrix* lhs) {
  const CompressedRowBlockStructure* bs = A.block_structure();
  const double* values = A.values();

  const CompressedRow& row = bs->rows[row_block_index];
  for (int i = 1; i < row.cells.size(); ++i) {
    const int block1 = row.cells[i].block_id - num_eliminate_blocks_;
    DCHECK_GE(block1, 0);

    const int block1_size = bs->cols[row.cells[i].block_id].size;
    int r, c, row_stride, col_stride;
    CellInfo* cell_info =
        lhs->GetCell(block1, block1, &r, &c, &row_stride, &col_stride);
    if (cell_info != nullptr) {
      auto lock = MakeConditionalLock(num_threads_, cell_info->m);
      // block += b1.transpose() * b1;
      // clang-format off
      MatrixTransposeMatrixMultiply
          <kRowBlockSize, kFBlockSize, kRowBlockSize, kFBlockSize, 1>(
          values + row.cells[i].position, row.block.size, block1_size,
          values + row.cells[i].position, row.block.size, block1_size,
          cell_info->values, r, c, row_stride, col_stride);
      // clang-format on
    }

    for (int j = i + 1; j < row.cells.size(); ++j) {
      const int block2 = row.cells[j].block_id - num_eliminate_blocks_;
      DCHECK_GE(block2, 0);
      DCHECK_LT(block1, block2);
      const int block2_size = bs->cols[row.cells[j].block_id].size;
      int r, c, row_stride, col_stride;
      CellInfo* cell_info =
          lhs->GetCell(block1, block2, &r, &c, &row_stride, &col_stride);
      if (cell_info != nullptr) {
        // block += b1.transpose() * b2;
        auto lock = MakeConditionalLock(num_threads_, cell_info->m);
        // clang-format off
        MatrixTransposeMatrixMultiply
            <kRowBlockSize, kFBlockSize, kRowBlockSize, kFBlockSize, 1>(
                values + row.cells[i].position, row.block.size, block1_size,
                values + row.cells[j].position, row.block.size, block2_size,
                cell_info->values, r, c, row_stride, col_stride);
        // clang-format on
      }
    }
  }
}
