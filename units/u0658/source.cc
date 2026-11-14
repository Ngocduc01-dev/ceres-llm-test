// u0658 – ceres::internal::EigenDenseQR::Factorize
// Trích từ internal/ceres/dense_qr.cc, dòng 162–170 (chỉ để xem, không compile)

LinearSolverTerminationType EigenDenseQR::Factorize(int num_rows,
                                                    int num_cols,
                                                    double* lhs,
                                                    std::string* message) {
  Eigen::Map<ColMajorMatrix> m(lhs, num_rows, num_cols);
  qr_ = std::make_unique<QRType>(m);
  *message = "Success.";
  return LinearSolverTerminationType::SUCCESS;
}
