// u1147 – ceres::internal::BlockSparseMatrixData::BlockSparseMatrixData
// Trích từ internal/ceres/block_sparse_matrix.h, dòng 186–187 (chỉ để xem, không compile)

  explicit BlockSparseMatrixData(const BlockSparseMatrix& m)
      : block_structure_(m.block_structure()), values_(m.values()){};
