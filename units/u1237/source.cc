// u1237 – ceres::internal::IterativeSchurComplementSolver::CreatePreconditioner
// Trích từ internal/ceres/iterative_schur_complement_solver.cc, dòng 158–198 (chỉ để xem, không compile)

void IterativeSchurComplementSolver::CreatePreconditioner(
    BlockSparseMatrix* A) {
  if (preconditioner_ != nullptr) {
    return;
  }

  Preconditioner::Options preconditioner_options(options_);
  CHECK(options_.context != nullptr);

  switch (options_.preconditioner_type) {
    case IDENTITY:
      preconditioner_ = std::make_unique<IdentityPreconditioner>(
          schur_complement_->num_cols());
      break;
    case JACOBI:
      preconditioner_ = std::make_unique<SparseMatrixPreconditionerWrapper>(
          schur_complement_->block_diagonal_FtF_inverse(),
          preconditioner_options);
      break;
    case SCHUR_POWER_SERIES_EXPANSION:
      // Ignoring the value of spse_tolerance to ensure preconditioner stays
      // fixed during the iterations of cg.
      preconditioner_ = std::make_unique<PowerSeriesExpansionPreconditioner>(
          schur_complement_.get(),
          options_.max_num_spse_iterations,
          0,
          preconditioner_options);
      break;
    case SCHUR_JACOBI:
      preconditioner_ = std::make_unique<SchurJacobiPreconditioner>(
          *A->block_structure(), preconditioner_options);
      break;
    case CLUSTER_JACOBI:
    case CLUSTER_TRIDIAGONAL:
      preconditioner_ = std::make_unique<VisibilityBasedPreconditioner>(
          *A->block_structure(), preconditioner_options);
      break;
    default:
      LOG(FATAL) << "Unknown Preconditioner Type";
  }
};
