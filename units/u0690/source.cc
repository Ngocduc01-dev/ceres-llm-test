// u0690 – ceres::internal::SparseMatrixPreconditionerWrapper::num_rows
// Trích từ internal/ceres/preconditioner.cc, dòng 69–71 (chỉ để xem, không compile)

int SparseMatrixPreconditionerWrapper::num_rows() const {
  return matrix_->num_rows();
}
