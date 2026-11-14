// u0949 – ceres::internal::CompressedRowSparseMatrix::DeleteRows
// Trích từ internal/ceres/compressed_row_sparse_matrix.cc, dòng 454–478 (chỉ để xem, không compile)

void CompressedRowSparseMatrix::DeleteRows(int delta_rows) {
  CHECK_GE(delta_rows, 0);
  CHECK_LE(delta_rows, num_rows_);
  CHECK_EQ(storage_type_, StorageType::UNSYMMETRIC);

  num_rows_ -= delta_rows;
  rows_.resize(num_rows_ + 1);

  // The rest of the code updates the block information. Immediately
  // return in case of no block information.
  if (row_blocks_.empty()) {
    return;
  }

  // Walk the list of row blocks until we reach the new number of rows
  // and the drop the rest of the row blocks.
  int num_row_blocks = 0;
  int num_rows = 0;
  while (num_row_blocks < row_blocks_.size() && num_rows < num_rows_) {
    num_rows += row_blocks_[num_row_blocks].size;
    ++num_row_blocks;
  }

  row_blocks_.resize(num_row_blocks);
}
