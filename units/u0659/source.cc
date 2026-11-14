// u0659 – ceres::internal::EigenDenseQR::Solve
// Trích từ internal/ceres/dense_qr.cc, dòng 172–179 (chỉ để xem, không compile)

LinearSolverTerminationType EigenDenseQR::Solve(const double* rhs,
                                                double* solution,
                                                std::string* message) {
  VectorRef(solution, qr_->cols()) =
      qr_->solve(ConstVectorRef(rhs, qr_->rows()));
  *message = "Success.";
  return LinearSolverTerminationType::SUCCESS;
}
