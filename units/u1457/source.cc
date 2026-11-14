// u1457 – ceres::internal::InnerProductComputer::Init
// Trích từ internal/ceres/inner_product_computer.cc, dòng 141–177 (chỉ để xem, không compile)

void InnerProductComputer::Init(
    const CompressedRowSparseMatrix::StorageType product_storage_type) {
  std::vector<InnerProductComputer::ProductTerm> product_terms;
  const CompressedRowBlockStructure* bs = m_.block_structure();

  // Give input matrix m in Block Sparse format
  //     (row_block, col_block)
  // represent each block multiplication
  //     (row_block, col_block1)' X (row_block, col_block2)
  // by its product term:
  //     (col_block1, col_block2, index)
  for (int row_block = start_row_block_; row_block < end_row_block_;
       ++row_block) {
    const CompressedRow& row = bs->rows[row_block];
    for (int c1 = 0; c1 < row.cells.size(); ++c1) {
      const Cell& cell1 = row.cells[c1];
      int c2_begin, c2_end;
      if (product_storage_type ==
          CompressedRowSparseMatrix::StorageType::LOWER_TRIANGULAR) {
        c2_begin = 0;
        c2_end = c1 + 1;
      } else {
        c2_begin = c1;
        c2_end = row.cells.size();
      }

      for (int c2 = c2_begin; c2 < c2_end; ++c2) {
        const Cell& cell2 = row.cells[c2];
        product_terms.emplace_back(
            cell1.block_id, cell2.block_id, product_terms.size());
      }
    }
  }

  std::sort(product_terms.begin(), product_terms.end());
  ComputeOffsetsAndCreateResultMatrix(product_storage_type, product_terms);
}
