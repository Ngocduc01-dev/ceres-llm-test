// u1371 – ceres::internal::SchurJacobiPreconditioner::UpdateImpl
// Trích từ internal/ceres/schur_jacobi_preconditioner.cc, dòng 87–97 (chỉ để xem, không compile)

bool SchurJacobiPreconditioner::UpdateImpl(const BlockSparseMatrix& A,
                                           const double* D) {
  const int num_rows = m_->num_rows();
  CHECK_GT(num_rows, 0);

  // Compute a subset of the entries of the Schur complement.
  eliminator_->Eliminate(
      BlockSparseMatrixData(A), nullptr, D, m_.get(), nullptr);
  m_->Invert();
  return true;
}
