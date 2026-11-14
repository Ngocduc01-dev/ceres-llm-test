// u1290 – ceres::internal::RefinedSparseCholesky::Solve
// Trích từ internal/ceres/sparse_cholesky.cc, dòng 139–150 (chỉ để xem, không compile)

LinearSolverTerminationType RefinedSparseCholesky::Solve(const double* rhs,
                                                         double* solution,
                                                         std::string* message) {
  CHECK(lhs_ != nullptr);
  auto termination_type = sparse_cholesky_->Solve(rhs, solution, message);
  if (termination_type != LinearSolverTerminationType::SUCCESS) {
    return termination_type;
  }

  iterative_refiner_->Refine(*lhs_, rhs, sparse_cholesky_.get(), solution);
  return LinearSolverTerminationType::SUCCESS;
}
