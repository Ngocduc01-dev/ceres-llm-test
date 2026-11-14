// u1183 – ceres::internal::DenseQR::Create
// Trích từ internal/ceres/dense_qr.cc, dòng 116–146 (chỉ để xem, không compile)

std::unique_ptr<DenseQR> DenseQR::Create(const LinearSolver::Options& options) {
  std::unique_ptr<DenseQR> dense_qr;

  switch (options.dense_linear_algebra_library_type) {
    case EIGEN:
      dense_qr = std::make_unique<EigenDenseQR>();
      break;

    case LAPACK:
#ifndef CERES_NO_LAPACK
      dense_qr = std::make_unique<LAPACKDenseQR>();
      break;
#else
      LOG(FATAL) << "Ceres was compiled without support for LAPACK.";
#endif

    case CUDA:
#ifndef CERES_NO_CUDA
      dense_qr = CUDADenseQR::Create(options);
      break;
#else
      LOG(FATAL) << "Ceres was compiled without support for CUDA.";
#endif

    default:
      LOG(FATAL) << "Unknown dense linear algebra library type : "
                 << DenseLinearAlgebraLibraryTypeToString(
                        options.dense_linear_algebra_library_type);
  }
  return dense_qr;
}
