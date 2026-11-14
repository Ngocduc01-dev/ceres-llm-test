// u1379 – ceres::internal::InnerProductComputer::ComputeOffsetsAndCreateResultMatrix
// Trích từ internal/ceres/inner_product_computer.cc, dòng 179–280 (chỉ để xem, không compile)

void InnerProductComputer::ComputeOffsetsAndCreateResultMatrix(
    const CompressedRowSparseMatrix::StorageType product_storage_type,
    const std::vector<InnerProductComputer::ProductTerm>& product_terms) {
  const std::vector<Block>& col_blocks = m_.block_structure()->cols;

  std::vector<int> row_block_nnz;
  const int num_nonzeros = ComputeNonzeros(product_terms, &row_block_nnz);

  result_ = CreateResultMatrix(product_storage_type, num_nonzeros);

  // Populate the row non-zero counts in the result matrix.
  int* crsm_rows = result_->mutable_rows();
  crsm_rows[0] = 0;
  for (int i = 0; i < col_blocks.size(); ++i) {
    for (int j = 0; j < col_blocks[i].size; ++j, ++crsm_rows) {
      *(crsm_rows + 1) = *crsm_rows + row_block_nnz[i];
    }
  }
  result_offsets_.resize(product_terms.size());
  if (num_nonzeros == 0) {
    return;
  }

  // The following macro FILL_CRSM_COL_BLOCK is key to understanding
  // how this class works.
  //
  // It does two things.
  //
  // Sets the value for the current term in the result_offsets_ array
  // and populates the cols array of the result matrix.
  //
  // row_block and col_block as the names imply, refer to the row and
  // column blocks of the current term.
  //
  // row_nnz is the number of nonzeros in the result_matrix at the
  // beginning of the first row of row_block.
  //
  // col_nnz is the number of nonzeros in the first row of the row
  // block that occur before the current column block, i.e. this is
  // sum of the sizes of all the column blocks in this row block that
  // came before this column block.
  //
  // Given these two numbers and the total number of nonzeros in this
  // row (nnz_in_row), we can now populate the cols array as follows:
  //
  // nnz + j * nnz_in_row is the beginning of the j^th row.
  //
  // nnz + j * nnz_in_row + col_nnz is the beginning of the column
  // block in the j^th row.
  //
  // nnz + j * nnz_in_row + col_nnz + k is then the j^th row and the
  // k^th column of the product block, whose value is
  //
  // col_blocks[col_block].position + k, which is the column number of
  // the k^th column of the current column block.
#define FILL_CRSM_COL_BLOCK                                \
  const int row_block = current->row;                      \
  const int col_block = current->col;                      \
  const int nnz_in_row = row_block_nnz[row_block];         \
  int* crsm_cols = result_->mutable_cols();                \
  result_offsets_[current->index] = nnz + col_nnz;         \
  for (int j = 0; j < col_blocks[row_block].size; ++j) {   \
    for (int k = 0; k < col_blocks[col_block].size; ++k) { \
      crsm_cols[nnz + j * nnz_in_row + col_nnz + k] =      \
          col_blocks[col_block].position + k;              \
    }                                                      \
  }

  int col_nnz = 0;
  int nnz = 0;

  // Process the first term.
  const InnerProductComputer::ProductTerm* current = product_terms.data();
  FILL_CRSM_COL_BLOCK;

  // Process the rest of the terms.
  for (int i = 1; i < product_terms.size(); ++i) {
    current = &product_terms[i];
    const InnerProductComputer::ProductTerm* previous = &product_terms[i - 1];

    // If the current term is the same as the previous term, then it
    // stores its product at the same location as the previous term.
    if (previous->row == current->row && previous->col == current->col) {
      result_offsets_[current->index] = result_offsets_[previous->index];
      continue;
    }

    if (previous->row == current->row) {
      // if the current and previous terms are in the same row block,
      // then they differ in the column block, in which case advance
      // col_nnz by the column size of the previous term.
      col_nnz += col_blocks[previous->col].size;
    } else {
      // If we have moved to a new row-block , then col_nnz is zero,
      // and nnz is set to the beginning of the row block.
      col_nnz = 0;
      nnz += row_block_nnz[previous->row] * col_blocks[previous->row].size;
    }

    FILL_CRSM_COL_BLOCK;
  }
}
