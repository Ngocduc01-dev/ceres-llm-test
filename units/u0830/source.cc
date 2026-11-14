// u0830 – ceres::internal::BlockSparseMatrix::block_structure
// Trích từ internal/ceres/block_sparse_matrix.cc, dòng 546–548 (chỉ để xem, không compile)

const CompressedRowBlockStructure* BlockSparseMatrix::block_structure() const {
  return block_structure_.get();
}
