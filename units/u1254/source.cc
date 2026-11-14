// u1254 – ceres::internal::SchurJacobiPreconditioner::RightMultiplyAndAccumulate
// Trích từ internal/ceres/schur_jacobi_preconditioner.cc, dòng 99–102 (chỉ để xem, không compile)

void SchurJacobiPreconditioner::RightMultiplyAndAccumulate(const double* x,
                                                           double* y) const {
  m_->RightMultiplyAndAccumulate(x, y);
}
