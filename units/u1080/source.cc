// u1080 – ceres::internal::SparseMatrixPreconditionerWrapper::RightMultiplyAndAccumulate
// Trích từ internal/ceres/preconditioner.cc, dòng 63–67 (chỉ để xem, không compile)

void SparseMatrixPreconditionerWrapper::RightMultiplyAndAccumulate(
    const double* x, double* y) const {
  matrix_->RightMultiplyAndAccumulate(
      x, y, options_.context, options_.num_threads);
}
