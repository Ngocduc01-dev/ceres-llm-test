// u1214 – ceres::internal::CompressedRowSparseMatrix::AppendRows
// Trích từ internal/ceres/compressed_row_sparse_matrix.cc, dòng 480–528 (chỉ để xem, không compile)

void CompressedRowSparseMatrix::AppendRows(const CompressedRowSparseMatrix& m) {
  CHECK_EQ(storage_type_, StorageType::UNSYMMETRIC);
  CHECK_EQ(m.num_cols(), num_cols_);

  CHECK((row_blocks_.empty() && m.row_blocks().empty()) ||
        (!row_blocks_.empty() && !m.row_blocks().empty()))
      << "Cannot append a matrix with row blocks to one without and vice versa."
      << "This matrix has : " << row_blocks_.size() << " row blocks."
      << "The matrix being appended has: " << m.row_blocks().size()
      << " row blocks.";

  if (m.num_rows() == 0) {
    return;
  }

  if (cols_.size() < num_nonzeros() + m.num_nonzeros()) {
    cols_.resize(num_nonzeros() + m.num_nonzeros());
    values_.resize(num_nonzeros() + m.num_nonzeros());
  }

  // Copy the contents of m into this matrix.
  DCHECK_LT(num_nonzeros(), cols_.size());
  if (m.num_nonzeros() > 0) {
    std::copy(m.cols(), m.cols() + m.num_nonzeros(), &cols_[num_nonzeros()]);
    std::copy(
        m.values(), m.values() + m.num_nonzeros(), &values_[num_nonzeros()]);
  }

  rows_.resize(num_rows_ + m.num_rows() + 1);
  // new_rows = [rows_, m.row() + rows_[num_rows_]]
  std::fill(rows_.begin() + num_rows_,
            rows_.begin() + num_rows_ + m.num_rows() + 1,
            rows_[num_rows_]);

  for (int r = 0; r < m.num_rows() + 1; ++r) {
    rows_[num_rows_ + r] += m.rows()[r];
  }

  num_rows_ += m.num_rows();

  // The rest of the code updates the block information. Immediately
  // return in case of no block information.
  if (row_blocks_.empty()) {
    return;
  }

  row_blocks_.insert(
      row_blocks_.end(), m.row_blocks().begin(), m.row_blocks().end());
}
