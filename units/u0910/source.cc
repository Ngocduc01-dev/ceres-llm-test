// u0910 – ceres::internal::SparseMatrixPreconditionerWrapper::SparseMatrixPreconditionerWrapper
// Trích từ internal/ceres/preconditioner.cc, dòng 49–53 (chỉ để xem, không compile)

SparseMatrixPreconditionerWrapper::SparseMatrixPreconditionerWrapper(
    const SparseMatrix* matrix, const Preconditioner::Options& options)
    : matrix_(matrix), options_(options) {
  CHECK(matrix != nullptr);
}
