// u0542 – ceres::internal::MatrixMatrixMultiply
// Trích từ internal/ceres/small_blas.h, dòng 246–262 (chỉ để xem, không compile)

CERES_GEMM_BEGIN(MatrixMatrixMultiply) {
#ifdef CERES_NO_CUSTOM_BLAS

  CERES_CALL_GEMM(MatrixMatrixMultiplyEigen)
  return;

#else

  if (kRowA != Eigen::Dynamic && kColA != Eigen::Dynamic &&
      kRowB != Eigen::Dynamic && kColB != Eigen::Dynamic) {
    CERES_CALL_GEMM(MatrixMatrixMultiplyEigen)
  } else {
    CERES_CALL_GEMM(MatrixMatrixMultiplyNaive)
  }

#endif
}
