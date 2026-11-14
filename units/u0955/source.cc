// u0955 – ceres::internal::LinearSolver::Create
// Trích từ internal/ceres/linear_solver.cc, dòng 74–127 (chỉ để xem, không compile)

std::unique_ptr<LinearSolver> LinearSolver::Create(
    const LinearSolver::Options& options) {
  CHECK(options.context != nullptr);

  switch (options.type) {
    case CGNR: {
#ifndef CERES_NO_CUDA
      if (options.sparse_linear_algebra_library_type == CUDA_SPARSE) {
        std::string error;
        return CudaCgnrSolver::Create(options, &error);
      }
#endif
      return std::make_unique<CgnrSolver>(options);
    } break;

    case SPARSE_NORMAL_CHOLESKY:
#if defined(CERES_NO_SPARSE)
      return nullptr;
#else
      if (options.dynamic_sparsity) {
        return std::make_unique<DynamicSparseNormalCholeskySolver>(options);
      }

      return std::make_unique<SparseNormalCholeskySolver>(options);
#endif

    case SPARSE_SCHUR:
#if defined(CERES_NO_SPARSE)
      return nullptr;
#else
      return std::make_unique<SparseSchurComplementSolver>(options);
#endif

    case DENSE_SCHUR:
      return std::make_unique<DenseSchurComplementSolver>(options);

    case ITERATIVE_SCHUR:
      if (options.use_explicit_schur_complement) {
        return std::make_unique<SparseSchurComplementSolver>(options);
      } else {
        return std::make_unique<IterativeSchurComplementSolver>(options);
      }

    case DENSE_QR:
      return std::make_unique<DenseQRSolver>(options);

    case DENSE_NORMAL_CHOLESKY:
      return std::make_unique<DenseNormalCholeskySolver>(options);

    default:
      LOG(FATAL) << "Unknown linear solver type :" << options.type;
      return nullptr;  // MSVC doesn't understand that LOG(FATAL) never returns.
  }
}
