// u1109 – ceres::internal::SchurEliminatorForOneFBlock::BackSubstitute
// Trích từ internal/ceres/schur_eliminator.h, dòng 571–612 (chỉ để xem, không compile)

  void BackSubstitute(const BlockSparseMatrixData& A,
                      const double* b,
                      const double* /*D*/,
                      const double* z_ptr,
                      double* y) override {
    typename EigenTypes<kFBlockSize>::ConstVectorRef z(z_ptr, kFBlockSize);
    const CompressedRowBlockStructure* bs = A.block_structure();
    const double* values = A.values();
    Eigen::Matrix<double, kEBlockSize, 1> tmp;
    for (int i = 0; i < chunks_.size(); ++i) {
      const Chunk& chunk = chunks_[i];
      const int e_block_id = bs->rows[chunk.start].cells.front().block_id;
      tmp.setZero();
      for (int j = 0; j < chunk.num_rows; ++j) {
        const int row_id = chunk.start + j;
        const auto& row = bs->rows[row_id];
        const typename EigenTypes<kRowBlockSize, kEBlockSize>::ConstMatrixRef
            e_block(values + row.cells[0].position, kRowBlockSize, kEBlockSize);
        const typename EigenTypes<kRowBlockSize>::ConstVectorRef b_block(
            b + row.block.position, kRowBlockSize);

        if (row.cells.size() == 1) {
          // There is no f block.
          tmp += e_block.transpose() * b_block;
        } else {
          typename EigenTypes<kRowBlockSize, kFBlockSize>::ConstMatrixRef
              f_block(
                  values + row.cells[1].position, kRowBlockSize, kFBlockSize);
          tmp += e_block.transpose() * (b_block - f_block * z);
        }
      }

      typename EigenTypes<kEBlockSize, kEBlockSize>::MatrixRef e_t_e_inverse(
          &e_t_e_inverse_matrices_[kEBlockSize * kEBlockSize * i],
          kEBlockSize,
          kEBlockSize);

      typename EigenTypes<kEBlockSize>::VectorRef y_block(
          y + bs->cols[e_block_id].position, kEBlockSize);
      y_block.noalias() = e_t_e_inverse * tmp;
    }
  }
