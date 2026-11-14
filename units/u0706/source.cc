// u0706 – ceres::internal::EigenDenseCholesky::Solve
// Trích từ internal/ceres/dense_cholesky.cc, dòng 163–175 (chỉ để xem, không compile)

LinearSolverTerminationType EigenDenseCholesky::Solve(const double* rhs,
                                                      double* solution,
                                                      std::string* message) {
  if (llt_->info() != Eigen::Success) {
    *message = "Eigen failure. Unable to perform dense Cholesky factorization.";
    return LinearSolverTerminationType::FAILURE;
  }

  VectorRef(solution, llt_->cols()) =
      llt_->solve(ConstVectorRef(rhs, llt_->cols()));
  *message = "Success.";
  return LinearSolverTerminationType::SUCCESS;
}
