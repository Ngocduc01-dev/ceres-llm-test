// u0543 – ceres::internal::MatrixTransposeMatrixMultiply
// Trích từ internal/ceres/small_blas.h, dòng 353–369 (chỉ để xem, không compile)

CERES_GEMM_BEGIN(MatrixTransposeMatrixMultiply) {
#ifdef CERES_NO_CUSTOM_BLAS

  CERES_CALL_GEMM(MatrixTransposeMatrixMultiplyEigen)
  return;

#else

  if (kRowA != Eigen::Dynamic && kColA != Eigen::Dynamic &&
      kRowB != Eigen::Dynamic && kColB != Eigen::Dynamic) {
    CERES_CALL_GEMM(MatrixTransposeMatrixMultiplyEigen)
  } else {
    CERES_CALL_GEMM(MatrixTransposeMatrixMultiplyNaive)
  }

#endif
}
