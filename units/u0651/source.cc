// u0651 – ceres::internal::BlockSparseMatrixData::BlockSparseMatrixData
// Trích từ internal/ceres/block_sparse_matrix.h, dòng 189–191 (chỉ để xem, không compile)

  BlockSparseMatrixData(const CompressedRowBlockStructure* block_structure,
                        const double* values)
      : block_structure_(block_structure), values_(values) {}
