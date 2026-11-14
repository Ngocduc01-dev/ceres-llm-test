// u1496 – ceres::internal::VisibilityBasedPreconditioner::UpdateImpl
// Trích từ internal/ceres/visibility_based_preconditioner.cc, dòng 318–361 (chỉ để xem, không compile)

bool VisibilityBasedPreconditioner::UpdateImpl(const BlockSparseMatrix& A,
                                               const double* D) {
  const time_t start_time = time(nullptr);
  const int num_rows = m_->num_rows();
  CHECK_GT(num_rows, 0);

  // Compute a subset of the entries of the Schur complement.
  eliminator_->Eliminate(
      BlockSparseMatrixData(A), nullptr, D, m_.get(), nullptr);

  // Try factorizing the matrix. For CLUSTER_JACOBI, this should
  // always succeed modulo some numerical/conditioning problems. For
  // CLUSTER_TRIDIAGONAL, in general the preconditioner matrix as
  // constructed is not positive definite. However, we will go ahead
  // and try factorizing it. If it works, great, otherwise we scale
  // all the cells in the preconditioner corresponding to the edges in
  // the degree-2 forest and that guarantees positive
  // definiteness. The proof of this fact can be found in Lemma 1 in
  // "Visibility Based Preconditioning for Bundle Adjustment".
  //
  // Doing the factorization like this saves us matrix mass when
  // scaling is not needed, which is quite often in our experience.
  LinearSolverTerminationType status = Factorize();

  if (status == LinearSolverTerminationType::FATAL_ERROR) {
    return false;
  }

  // The scaling only affects the tri-diagonal case, since
  // ScaleOffDiagonalBlocks only pays attention to the cells that
  // belong to the edges of the degree-2 forest. In the CLUSTER_JACOBI
  // case, the preconditioner is guaranteed to be positive
  // semidefinite.
  if (status == LinearSolverTerminationType::FAILURE &&
      options_.type == CLUSTER_TRIDIAGONAL) {
    VLOG(1) << "Unscaled factorization failed. Retrying with off-diagonal "
            << "scaling";
    ScaleOffDiagonalCells();
    status = Factorize();
  }

  VLOG(2) << "Compute time: " << time(nullptr) - start_time;
  return (status == LinearSolverTerminationType::SUCCESS);
}
