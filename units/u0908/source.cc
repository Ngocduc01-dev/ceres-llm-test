// u0908 – ceres::internal::ImplicitSchurComplement::block_diagonal_FtF_inverse
// Trích từ internal/ceres/implicit_schur_complement.h, dòng 145–148 (chỉ để xem, không compile)

  const BlockSparseMatrix* block_diagonal_FtF_inverse() const {
    CHECK(compute_ftf_inverse_);
    return block_diagonal_FtF_inverse_.get();
  }
