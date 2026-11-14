// u1454 – ceres::internal::SparseNormalCholeskySolver::SolveImpl
// Trích từ internal/ceres/sparse_normal_cholesky_solver.cc, dòng 58–110 (chỉ để xem, không compile)

LinearSolver::Summary SparseNormalCholeskySolver::SolveImpl(
    BlockSparseMatrix* A,
    const double* b,
    const LinearSolver::PerSolveOptions& per_solve_options,
    double* x) {
  EventLogger event_logger("SparseNormalCholeskySolver::Solve");
  LinearSolver::Summary summary;
  summary.num_iterations = 1;
  summary.termination_type = LinearSolverTerminationType::SUCCESS;
  summary.message = "Success.";

  const int num_cols = A->num_cols();
  VectorRef xref(x, num_cols);
  xref.setZero();
  rhs_.resize(num_cols);
  rhs_.setZero();
  A->LeftMultiplyAndAccumulate(b, rhs_.data());
  event_logger.AddEvent("Compute RHS");

  if (per_solve_options.D != nullptr) {
    // Temporarily append a diagonal block to the A matrix, but undo
    // it before returning the matrix to the user.
    std::unique_ptr<BlockSparseMatrix> regularizer =
        BlockSparseMatrix::CreateDiagonalMatrix(per_solve_options.D,
                                                A->block_structure()->cols);
    event_logger.AddEvent("Diagonal");
    A->AppendRows(*regularizer);
    event_logger.AddEvent("Append");
  }
  event_logger.AddEvent("Append Rows");

  if (inner_product_computer_.get() == nullptr) {
    inner_product_computer_ =
        InnerProductComputer::Create(*A, sparse_cholesky_->StorageType());

    event_logger.AddEvent("InnerProductComputer::Create");
  }

  inner_product_computer_->Compute();
  event_logger.AddEvent("InnerProductComputer::Compute");

  if (per_solve_options.D != nullptr) {
    A->DeleteRowBlocks(A->block_structure()->cols.size());
  }

  summary.termination_type = sparse_cholesky_->FactorAndSolve(
      inner_product_computer_->mutable_result(),
      rhs_.data(),
      x,
      &summary.message);
  event_logger.AddEvent("SparseCholesky::FactorAndSolve");
  return summary;
}
