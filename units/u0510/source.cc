// u0510 – ceres::internal::MatrixMatrixMultiplyEigen
// Trích từ internal/ceres/small_blas.h, dòng 163–175 (chỉ để xem, không compile)

CERES_GEMM_BEGIN(MatrixMatrixMultiplyEigen) {
  CERES_GEMM_EIGEN_HEADER
  Eigen::Block<MatrixRef, kRowA, kColB> block(
      Cref, start_row_c, start_col_c, num_row_a, num_col_b);

  if (kOperation > 0) {
    block.noalias() += Aref * Bref;
  } else if (kOperation < 0) {
    block.noalias() -= Aref * Bref;
  } else {
    block.noalias() = Aref * Bref;
  }
}
