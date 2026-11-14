// u1123 – ceres::internal::SchurEliminatorForOneFBlock::Eliminate
// Trích từ internal/ceres/schur_eliminator.h, dòng 430–565 (chỉ để xem, không compile)

  void Eliminate(const BlockSparseMatrixData& A,
                 const double* b,
                 const double* D,
                 BlockRandomAccessMatrix* lhs_bram,
                 double* rhs_ptr) override {
    // Since there is only one f-block, we can call GetCell once, and cache its
    // output.
    int r, c, row_stride, col_stride;
    CellInfo* cell_info =
        lhs_bram->GetCell(0, 0, &r, &c, &row_stride, &col_stride);
    typename EigenTypes<kFBlockSize, kFBlockSize>::MatrixRef lhs(
        cell_info->values, kFBlockSize, kFBlockSize);
    typename EigenTypes<kFBlockSize>::VectorRef rhs(rhs_ptr, kFBlockSize);

    lhs.setZero();
    rhs.setZero();

    const CompressedRowBlockStructure* bs = A.block_structure();
    const double* values = A.values();

    // Add the diagonal to the Schur complement.
    if (D != nullptr) {
      typename EigenTypes<kFBlockSize>::ConstVectorRef diag(
          D + bs->cols[num_eliminate_blocks_].position, kFBlockSize);
      lhs.diagonal() = diag.array().square().matrix();
    }

    Eigen::Matrix<double, kEBlockSize, kFBlockSize> tmp;
    Eigen::Matrix<double, kEBlockSize, 1> tmp2;

    // The following loop works on a block matrix which looks as follows
    // (number of rows can be anything):
    //
    // [e_1 | f_1] = [b1]
    // [e_2 | f_2] = [b2]
    // [e_3 | f_3] = [b3]
    // [e_4 | f_4] = [b4]
    //
    // and computes the following
    //
    // e_t_e = sum_i e_i^T * e_i
    // e_t_e_inverse = inverse(e_t_e)
    // e_t_f = sum_i e_i^T f_i
    // e_t_b = sum_i e_i^T b_i
    // f_t_b = sum_i f_i^T b_i
    //
    // lhs += sum_i f_i^T * f_i - e_t_f^T * e_t_e_inverse * e_t_f
    // rhs += f_t_b - e_t_f^T * e_t_e_inverse * e_t_b
    for (int i = 0; i < chunks_.size(); ++i) {
      const Chunk& chunk = chunks_[i];
      const int e_block_id = bs->rows[chunk.start].cells.front().block_id;

      // Naming convention, e_t_e = e_block.transpose() * e_block;
      Eigen::Matrix<double, kEBlockSize, kEBlockSize> e_t_e;
      Eigen::Matrix<double, kEBlockSize, kFBlockSize> e_t_f;
      Eigen::Matrix<double, kEBlockSize, 1> e_t_b;
      Eigen::Matrix<double, kFBlockSize, 1> f_t_b;

      // Add the square of the diagonal to e_t_e.
      if (D != nullptr) {
        const typename EigenTypes<kEBlockSize>::ConstVectorRef diag(
            D + bs->cols[e_block_id].position, kEBlockSize);
        e_t_e = diag.array().square().matrix().asDiagonal();
      } else {
        e_t_e.setZero();
      }
      e_t_f.setZero();
      e_t_b.setZero();
      f_t_b.setZero();

      for (int j = 0; j < chunk.num_rows; ++j) {
        const int row_id = chunk.start + j;
        const auto& row = bs->rows[row_id];
        const typename EigenTypes<kRowBlockSize, kEBlockSize>::ConstMatrixRef
            e_block(values + row.cells[0].position, kRowBlockSize, kEBlockSize);
        const typename EigenTypes<kRowBlockSize>::ConstVectorRef b_block(
            b + row.block.position, kRowBlockSize);

        e_t_e.noalias() += e_block.transpose() * e_block;
        e_t_b.noalias() += e_block.transpose() * b_block;

        if (row.cells.size() == 1) {
          // There is no f block, so there is nothing more to do.
          continue;
        }

        const typename EigenTypes<kRowBlockSize, kFBlockSize>::ConstMatrixRef
            f_block(values + row.cells[1].position, kRowBlockSize, kFBlockSize);
        e_t_f.noalias() += e_block.transpose() * f_block;
        lhs.noalias() += f_block.transpose() * f_block;
        f_t_b.noalias() += f_block.transpose() * b_block;
      }

      // BackSubstitute computes the same inverse, and this is the key workload
      // there, so caching these inverses makes BackSubstitute essentially free.
      typename EigenTypes<kEBlockSize, kEBlockSize>::MatrixRef e_t_e_inverse(
          &e_t_e_inverse_matrices_[kEBlockSize * kEBlockSize * i],
          kEBlockSize,
          kEBlockSize);

      // e_t_e is a symmetric positive definite matrix, so the standard way to
      // compute its inverse is via the Cholesky factorization by calling
      // e_t_e.llt().solve(Identity()). However, the inverse() method even
      // though it is not optimized for symmetric matrices is significantly
      // faster for small fixed size (up to 4x4) matrices.
      //
      // https://eigen.tuxfamily.org/dox/group__TutorialLinearAlgebra.html#title3
      e_t_e_inverse.noalias() = e_t_e.inverse();

      // The use of these two pre-allocated tmp vectors saves temporaries in the
      // expressions for lhs and rhs updates below and has a significant impact
      // on the performance of this method.
      tmp.noalias() = e_t_e_inverse * e_t_f;
      tmp2.noalias() = e_t_e_inverse * e_t_b;

      lhs.noalias() -= e_t_f.transpose() * tmp;
      rhs.noalias() += f_t_b - e_t_f.transpose() * tmp2;
    }

    // The rows without any e-blocks can have arbitrary size but only contain
    // the f-block.
    //
    // lhs += f_i^T f_i
    // rhs += f_i^T b_i
    for (int row_id = uneliminated_row_begins_; row_id < bs->rows.size();
         ++row_id) {
      const auto& row = bs->rows[row_id];
      const auto& cell = row.cells[0];
      const typename EigenTypes<Eigen::Dynamic, kFBlockSize>::ConstMatrixRef
          f_block(values + cell.position, row.block.size, kFBlockSize);
      const typename EigenTypes<Eigen::Dynamic>::ConstVectorRef b_block(
          b + row.block.position, row.block.size);
      lhs.noalias() += f_block.transpose() * f_block;
      rhs.noalias() += f_block.transpose() * b_block;
    }
  }
