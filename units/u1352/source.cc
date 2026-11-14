// u1352 – ceres::internal::SubsetPreconditioner::SubsetPreconditioner
// Trích từ internal/ceres/subset_preconditioner.cc, dòng 45–56 (chỉ để xem, không compile)

SubsetPreconditioner::SubsetPreconditioner(Preconditioner::Options options,
                                           const BlockSparseMatrix& A)
    : options_(std::move(options)), num_cols_(A.num_cols()) {
  CHECK_GE(options_.subset_preconditioner_start_row_block, 0)
      << "Congratulations, you found a bug in Ceres. Please report it.";

  LinearSolver::Options sparse_cholesky_options;
  sparse_cholesky_options.sparse_linear_algebra_library_type =
      options_.sparse_linear_algebra_library_type;
  sparse_cholesky_options.ordering_type = options_.ordering_type;
  sparse_cholesky_ = SparseCholesky::Create(sparse_cholesky_options);
}
