// u1494 – ceres::internal::DynamicSparseNormalCholeskySolver::SolveImpl
// Trích từ internal/ceres/dynamic_sparse_normal_cholesky_solver.cc, dòng 60–103 (chỉ để xem, không compile)

LinearSolver::Summary DynamicSparseNormalCholeskySolver::SolveImpl(
    CompressedRowSparseMatrix* A,
    const double* b,
    const LinearSolver::PerSolveOptions& per_solve_options,
    double* x) {
  const int num_cols = A->num_cols();
  VectorRef(x, num_cols).setZero();
  A->LeftMultiplyAndAccumulate(b, x);

  if (per_solve_options.D != nullptr) {
    // Temporarily append a diagonal block to the A matrix, but undo
    // it before returning the matrix to the user.
    std::unique_ptr<CompressedRowSparseMatrix> regularizer;
    if (!A->col_blocks().empty()) {
      regularizer = CompressedRowSparseMatrix::CreateBlockDiagonalMatrix(
          per_solve_options.D, A->col_blocks());
    } else {
      regularizer = std::make_unique<CompressedRowSparseMatrix>(
          per_solve_options.D, num_cols);
    }
    A->AppendRows(*regularizer);
  }

  LinearSolver::Summary summary;
  switch (options_.sparse_linear_algebra_library_type) {
    case SUITE_SPARSE:
      summary = SolveImplUsingSuiteSparse(A, x);
      break;
    case EIGEN_SPARSE:
      summary = SolveImplUsingEigen(A, x);
      break;
    default:
      LOG(FATAL) << "Unsupported sparse linear algebra library for "
                 << "dynamic sparsity: "
                 << SparseLinearAlgebraLibraryTypeToString(
                        options_.sparse_linear_algebra_library_type);
  }

  if (per_solve_options.D != nullptr) {
    A->DeleteRows(num_cols);
  }

  return summary;
}
