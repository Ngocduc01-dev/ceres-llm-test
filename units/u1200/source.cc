// u1200 – ceres::internal::DenseCholesky::Create
// Trích từ internal/ceres/dense_cholesky.cc, dòng 81–134 (chỉ để xem, không compile)

std::unique_ptr<DenseCholesky> DenseCholesky::Create(
    const LinearSolver::Options& options) {
  std::unique_ptr<DenseCholesky> dense_cholesky;

  switch (options.dense_linear_algebra_library_type) {
    case EIGEN:
      // Eigen mixed precision solver not yet implemented.
      if (options.use_mixed_precision_solves) {
        dense_cholesky = std::make_unique<FloatEigenDenseCholesky>();
      } else {
        dense_cholesky = std::make_unique<EigenDenseCholesky>();
      }
      break;

    case LAPACK:
#ifndef CERES_NO_LAPACK
      // LAPACK mixed precision solver not yet implemented.
      if (options.use_mixed_precision_solves) {
        dense_cholesky = std::make_unique<FloatLAPACKDenseCholesky>();
      } else {
        dense_cholesky = std::make_unique<LAPACKDenseCholesky>();
      }
      break;
#else
      LOG(FATAL) << "Ceres was compiled without support for LAPACK.";
#endif

    case CUDA:
#ifndef CERES_NO_CUDA
      if (options.use_mixed_precision_solves) {
        dense_cholesky = CUDADenseCholeskyMixedPrecision::Create(options);
      } else {
        dense_cholesky = CUDADenseCholesky::Create(options);
      }
      break;
#else
      LOG(FATAL) << "Ceres was compiled without support for CUDA.";
#endif

    default:
      LOG(FATAL) << "Unknown dense linear algebra library type : "
                 << DenseLinearAlgebraLibraryTypeToString(
                        options.dense_linear_algebra_library_type);
  }

  if (options.max_num_refinement_iterations > 0) {
    auto refiner = std::make_unique<DenseIterativeRefiner>(
        options.max_num_refinement_iterations);
    dense_cholesky = std::make_unique<RefinedDenseCholesky>(
        std::move(dense_cholesky), std::move(refiner));
  }

  return dense_cholesky;
}
