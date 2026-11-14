// u1203 – ceres::internal::SparseCholesky::Create
// Trích từ internal/ceres/sparse_cholesky.cc, dòng 44–104 (chỉ để xem, không compile)

std::unique_ptr<SparseCholesky> SparseCholesky::Create(
    const LinearSolver::Options& options) {
  std::unique_ptr<SparseCholesky> sparse_cholesky;

  switch (options.sparse_linear_algebra_library_type) {
    case SUITE_SPARSE:
#ifndef CERES_NO_SUITESPARSE
      if (options.use_mixed_precision_solves) {
        sparse_cholesky =
            FloatSuiteSparseCholesky::Create(options.ordering_type);
      } else {
        sparse_cholesky = SuiteSparseCholesky::Create(options.ordering_type);
      }
      break;
#else
      LOG(FATAL) << "Ceres was compiled without support for SuiteSparse.";
#endif

    case EIGEN_SPARSE:
#ifdef CERES_USE_EIGEN_SPARSE
      if (options.use_mixed_precision_solves) {
        sparse_cholesky =
            FloatEigenSparseCholesky::Create(options.ordering_type);
      } else {
        sparse_cholesky = EigenSparseCholesky::Create(options.ordering_type);
      }
      break;
#else
      LOG(FATAL) << "Ceres was compiled without support for "
                 << "Eigen's sparse Cholesky factorization routines.";
#endif

    case ACCELERATE_SPARSE:
#ifndef CERES_NO_ACCELERATE_SPARSE
      if (options.use_mixed_precision_solves) {
        sparse_cholesky =
            AppleAccelerateCholesky<float>::Create(options.ordering_type);
      } else {
        sparse_cholesky =
            AppleAccelerateCholesky<double>::Create(options.ordering_type);
      }
      break;
#else
      LOG(FATAL) << "Ceres was compiled without support for Apple's Accelerate "
                 << "framework solvers.";
#endif

    default:
      LOG(FATAL) << "Unknown sparse linear algebra library type : "
                 << SparseLinearAlgebraLibraryTypeToString(
                        options.sparse_linear_algebra_library_type);
  }

  if (options.max_num_refinement_iterations > 0) {
    auto refiner = std::make_unique<SparseIterativeRefiner>(
        options.max_num_refinement_iterations);
    sparse_cholesky = std::make_unique<RefinedSparseCholesky>(
        std::move(sparse_cholesky), std::move(refiner));
  }
  return sparse_cholesky;
}
