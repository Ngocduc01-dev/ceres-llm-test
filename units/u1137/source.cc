// u1137 – ceres::internal::InnerProductComputer::ComputeNonzeros
// Trích từ internal/ceres/inner_product_computer.cc, dòng 64–96 (chỉ để xem, không compile)

int InnerProductComputer::ComputeNonzeros(
    const std::vector<InnerProductComputer::ProductTerm>& product_terms,
    std::vector<int>* row_nnz) {
  const CompressedRowBlockStructure* bs = m_.block_structure();
  const std::vector<Block>& blocks = bs->cols;

  row_nnz->resize(blocks.size());
  std::fill(row_nnz->begin(), row_nnz->end(), 0);

  if (product_terms.empty()) {
    return 0;
  }

  // First product term.
  (*row_nnz)[product_terms[0].row] = blocks[product_terms[0].col].size;
  int num_nonzeros =
      blocks[product_terms[0].row].size * blocks[product_terms[0].col].size;

  // Remaining product terms.
  for (int i = 1; i < product_terms.size(); ++i) {
    const ProductTerm& previous = product_terms[i - 1];
    const ProductTerm& current = product_terms[i];

    // Each (row, col) block counts only once.
    // This check depends on product sorted on (row, col).
    if (current.row != previous.row || current.col != previous.col) {
      (*row_nnz)[current.row] += blocks[current.col].size;
      num_nonzeros += blocks[current.row].size * blocks[current.col].size;
    }
  }

  return num_nonzeros;
}
