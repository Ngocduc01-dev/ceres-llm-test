// u0892 – ceres::internal::RefinedSparseCholesky::Factorize
// Trích từ internal/ceres/sparse_cholesky.cc, dòng 133–137 (chỉ để xem, không compile)

LinearSolverTerminationType RefinedSparseCholesky::Factorize(
    CompressedRowSparseMatrix* lhs, std::string* message) {
  lhs_ = lhs;
  return sparse_cholesky_->Factorize(lhs, message);
}
