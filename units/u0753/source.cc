// u0753 – ceres::internal::Preconditioner::PreconditionerForZeroEBlocks
// Trích từ internal/ceres/preconditioner.cc, dòng 39–47 (chỉ để xem, không compile)

PreconditionerType Preconditioner::PreconditionerForZeroEBlocks(
    PreconditionerType preconditioner_type) {
  if (preconditioner_type == SCHUR_JACOBI ||
      preconditioner_type == CLUSTER_JACOBI ||
      preconditioner_type == CLUSTER_TRIDIAGONAL) {
    return JACOBI;
  }
  return preconditioner_type;
}
