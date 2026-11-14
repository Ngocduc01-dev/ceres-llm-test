// u1211 – ceres::internal::BlockSparseMatrix::AppendRows
// Trích từ internal/ceres/block_sparse_matrix.cc, dòng 616–667 (chỉ để xem, không compile)

void BlockSparseMatrix::AppendRows(const BlockSparseMatrix& m) {
  CHECK_EQ(m.num_cols(), num_cols());
  const CompressedRowBlockStructure* m_bs = m.block_structure();
  CHECK_EQ(m_bs->cols.size(), block_structure_->cols.size());

  const int old_num_nonzeros = num_nonzeros_;
  const int old_num_row_blocks = block_structure_->rows.size();
  block_structure_->rows.resize(old_num_row_blocks + m_bs->rows.size());

  for (int i = 0; i < m_bs->rows.size(); ++i) {
    const CompressedRow& m_row = m_bs->rows[i];
    const int row_block_id = old_num_row_blocks + i;
    CompressedRow& row = block_structure_->rows[row_block_id];
    row.block.size = m_row.block.size;
    row.block.position = num_rows_;
    num_rows_ += m_row.block.size;
    row.cells.resize(m_row.cells.size());
    if (transpose_block_structure_) {
      transpose_block_structure_->cols.emplace_back(row.block);
    }
    for (int c = 0; c < m_row.cells.size(); ++c) {
      const int block_id = m_row.cells[c].block_id;
      row.cells[c].block_id = block_id;
      row.cells[c].position = num_nonzeros_;

      const int cell_nnz = m_row.block.size * m_bs->cols[block_id].size;
      if (transpose_block_structure_) {
        transpose_block_structure_->rows[block_id].cells.emplace_back(
            row_block_id, num_nonzeros_);
        transpose_block_structure_->rows[block_id].nnz += cell_nnz;
      }

      num_nonzeros_ += cell_nnz;
    }
  }

  if (num_nonzeros_ > max_num_nonzeros_) {
    double* old_values = values_;
    values_ = AllocateValues(num_nonzeros_);
    std::copy_n(old_values, old_num_nonzeros, values_);
    max_num_nonzeros_ = num_nonzeros_;
    FreeValues(old_values);
  }

  std::copy(
      m.values(), m.values() + m.num_nonzeros(), values_ + old_num_nonzeros);

  if (transpose_block_structure_ == nullptr) {
    return;
  }
  ComputeCumulativeNumberOfNonZeros(transpose_block_structure_->rows);
}
