// u0511 – ceres::internal::MatrixTransposeMatrixMultiplyEigen
// Trích từ internal/ceres/small_blas.h, dòng 264–278 (chỉ để xem, không compile)

CERES_GEMM_BEGIN(MatrixTransposeMatrixMultiplyEigen) {
  CERES_GEMM_EIGEN_HEADER
  // clang-format off
  Eigen::Block<MatrixRef, kColA, kColB> block(Cref,
                                              start_row_c, start_col_c,
                                              num_col_a, num_col_b);
  // clang-format on
  if (kOperation > 0) {
    block.noalias() += Aref.transpose() * Bref;
  } else if (kOperation < 0) {
    block.noalias() -= Aref.transpose() * Bref;
  } else {
    block.noalias() = Aref.transpose() * Bref;
  }
}
