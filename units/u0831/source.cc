// u0831 – ceres::internal::BlockSparseMatrix::transpose_block_structure
// Trích từ internal/ceres/block_sparse_matrix.cc, dòng 552–555 (chỉ để xem, không compile)

const CompressedRowBlockStructure*
BlockSparseMatrix::transpose_block_structure() const {
  return transpose_block_structure_.get();
}
