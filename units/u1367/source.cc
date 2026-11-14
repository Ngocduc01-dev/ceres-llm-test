// u1367 – ceres::internal::ImplicitSchurComplement::Init
// Trích từ internal/ceres/implicit_schur_complement.cc, dòng 49–97 (chỉ để xem, không compile)

void ImplicitSchurComplement::Init(const BlockSparseMatrix& A,
                                   const double* D,
                                   const double* b) {
  // Since initialization is reasonably heavy, perhaps we can save on
  // constructing a new object everytime.
  if (A_ == nullptr) {
    A_ = PartitionedMatrixViewBase::Create(options_, A);
  }

  D_ = D;
  b_ = b;

  compute_ftf_inverse_ =
      options_.use_spse_initialization ||
      options_.preconditioner_type == JACOBI ||
      options_.preconditioner_type == SCHUR_POWER_SERIES_EXPANSION;

  // Initialize temporary storage and compute the block diagonals of
  // E'E and F'E.
  if (block_diagonal_EtE_inverse_ == nullptr) {
    block_diagonal_EtE_inverse_ = A_->CreateBlockDiagonalEtE();
    if (compute_ftf_inverse_) {
      block_diagonal_FtF_inverse_ = A_->CreateBlockDiagonalFtF();
    }
    rhs_.resize(A_->num_cols_f());
    rhs_.setZero();
    tmp_rows_.resize(A_->num_rows());
    tmp_e_cols_.resize(A_->num_cols_e());
    tmp_e_cols_2_.resize(A_->num_cols_e());
    tmp_f_cols_.resize(A_->num_cols_f());
  } else {
    A_->UpdateBlockDiagonalEtE(block_diagonal_EtE_inverse_.get());
    if (compute_ftf_inverse_) {
      A_->UpdateBlockDiagonalFtF(block_diagonal_FtF_inverse_.get());
    }
  }

  // The block diagonals of the augmented linear system contain
  // contributions from the diagonal D if it is non-null. Add that to
  // the block diagonals and invert them.
  AddDiagonalAndInvert(D_, block_diagonal_EtE_inverse_.get());
  if (compute_ftf_inverse_) {
    AddDiagonalAndInvert((D_ == nullptr) ? nullptr : D_ + A_->num_cols_e(),
                         block_diagonal_FtF_inverse_.get());
  }

  // Compute the RHS of the Schur complement system.
  UpdateRhs();
}
