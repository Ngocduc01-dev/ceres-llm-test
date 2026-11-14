// u1349 – ceres::internal::BlockSparseMatrix::AddTransposeBlockStructure
// Trích từ internal/ceres/block_sparse_matrix.cc, dòng 219–223 (chỉ để xem, không compile)

void BlockSparseMatrix::AddTransposeBlockStructure() {
  if (transpose_block_structure_ == nullptr) {
    transpose_block_structure_ = CreateTranspose(*block_structure_);
  }
}
