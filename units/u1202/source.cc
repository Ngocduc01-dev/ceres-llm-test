// u1202 – ceres::internal::InnerProductComputer::Compute
// Trích từ internal/ceres/inner_product_computer.cc, dòng 286–334 (chỉ để xem, không compile)

void InnerProductComputer::Compute() {
  const double* m_values = m_.values();
  const CompressedRowBlockStructure* bs = m_.block_structure();

  const CompressedRowSparseMatrix::StorageType storage_type =
      result_->storage_type();
  result_->SetZero();
  double* values = result_->mutable_values();
  const int* rows = result_->rows();
  int cursor = 0;

  // Iterate row blocks.
  for (int r = start_row_block_; r < end_row_block_; ++r) {
    const CompressedRow& m_row = bs->rows[r];
    for (int c1 = 0; c1 < m_row.cells.size(); ++c1) {
      const Cell& cell1 = m_row.cells[c1];
      const int c1_size = bs->cols[cell1.block_id].size;
      const int row_nnz = rows[bs->cols[cell1.block_id].position + 1] -
                          rows[bs->cols[cell1.block_id].position];

      int c2_begin, c2_end;
      if (storage_type ==
          CompressedRowSparseMatrix::StorageType::LOWER_TRIANGULAR) {
        c2_begin = 0;
        c2_end = c1 + 1;
      } else {
        c2_begin = c1;
        c2_end = m_row.cells.size();
      }

      for (int c2 = c2_begin; c2 < c2_end; ++c2, ++cursor) {
        const Cell& cell2 = m_row.cells[c2];
        const int c2_size = bs->cols[cell2.block_id].size;
        // clang-format off
        MatrixTransposeMatrixMultiply<Eigen::Dynamic, Eigen::Dynamic,
                                      Eigen::Dynamic, Eigen::Dynamic, 1>(
                                          m_values + cell1.position,
                                          m_row.block.size, c1_size,
                                          m_values + cell2.position,
                                          m_row.block.size, c2_size,
                                          values + result_offsets_[cursor],
                                          0, 0, c1_size, row_nnz);
        // clang-format on
      }
    }
  }

  CHECK_EQ(cursor, result_offsets_.size());
}
