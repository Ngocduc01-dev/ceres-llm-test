// u0721 – ceres::internal::RefinedDenseCholesky::Solve
// Trích từ internal/ceres/dense_cholesky.cc, dòng 334–346 (chỉ để xem, không compile)

LinearSolverTerminationType RefinedDenseCholesky::Solve(const double* rhs,
                                                        double* solution,
                                                        std::string* message) {
  CHECK(lhs_ != nullptr);
  auto termination_type = dense_cholesky_->Solve(rhs, solution, message);
  if (termination_type != LinearSolverTerminationType::SUCCESS) {
    return termination_type;
  }

  iterative_refiner_->Refine(
      num_cols_, lhs_, rhs, dense_cholesky_.get(), solution);
  return LinearSolverTerminationType::SUCCESS;
}
