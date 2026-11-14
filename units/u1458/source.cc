// u1458 – ceres::internal::SparseSchurComplementSolver::SolveReducedLinearSystem
// Trích từ internal/ceres/schur_complement_solver.cc, dòng 290–333 (chỉ để xem, không compile)

LinearSolver::Summary SparseSchurComplementSolver::SolveReducedLinearSystem(
    const LinearSolver::PerSolveOptions& per_solve_options, double* solution) {
  if (options().type == ITERATIVE_SCHUR) {
    return SolveReducedLinearSystemUsingConjugateGradients(per_solve_options,
                                                           solution);
  }

  LinearSolver::Summary summary;
  summary.num_iterations = 0;
  summary.termination_type = LinearSolverTerminationType::SUCCESS;
  summary.message = "Success.";

  const BlockSparseMatrix* bsm =
      down_cast<const BlockRandomAccessSparseMatrix*>(lhs())->matrix();
  if (bsm->num_rows() == 0) {
    return summary;
  }

  const CompressedRowSparseMatrix::StorageType storage_type =
      sparse_cholesky_->StorageType();
  if (storage_type ==
      CompressedRowSparseMatrix::StorageType::UPPER_TRIANGULAR) {
    if (!crs_lhs_) {
      crs_lhs_ = bsm->ToCompressedRowSparseMatrix();
      crs_lhs_->set_storage_type(
          CompressedRowSparseMatrix::StorageType::UPPER_TRIANGULAR);
    } else {
      bsm->UpdateCompressedRowSparseMatrix(crs_lhs_.get());
    }
  } else {
    if (!crs_lhs_) {
      crs_lhs_ = bsm->ToCompressedRowSparseMatrixTranspose();
      crs_lhs_->set_storage_type(
          CompressedRowSparseMatrix::StorageType::LOWER_TRIANGULAR);
    } else {
      bsm->UpdateCompressedRowSparseMatrixTranspose(crs_lhs_.get());
    }
  }

  summary.num_iterations = 1;
  summary.termination_type = sparse_cholesky_->FactorAndSolve(
      crs_lhs_.get(), rhs().data(), solution, &summary.message);
  return summary;
}
