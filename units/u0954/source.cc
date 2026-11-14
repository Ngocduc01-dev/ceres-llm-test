// u0954 – ceres::internal::Evaluator::Create
// Trích từ internal/ceres/evaluator.cc, dòng 53–95 (chỉ để xem, không compile)

std::unique_ptr<Evaluator> Evaluator::Create(const Evaluator::Options& options,
                                             Program* program,
                                             std::string* error) {
  CHECK(options.context != nullptr);

  switch (options.linear_solver_type) {
    case DENSE_QR:
    case DENSE_NORMAL_CHOLESKY:
      return std::make_unique<
          ProgramEvaluator<ScratchEvaluatePreparer, DenseJacobianWriter>>(
          options, program);
    case DENSE_SCHUR:
    case SPARSE_SCHUR:
    case ITERATIVE_SCHUR:
    case CGNR: {
      if (options.sparse_linear_algebra_library_type == CUDA_SPARSE) {
        return std::make_unique<ProgramEvaluator<ScratchEvaluatePreparer,
                                                 CompressedRowJacobianWriter>>(
            options, program);
      } else {
        return std::make_unique<
            ProgramEvaluator<BlockEvaluatePreparer, BlockJacobianWriter>>(
            options, program);
      }
    }
    case SPARSE_NORMAL_CHOLESKY:
      if (options.dynamic_sparsity) {
        return std::make_unique<
            ProgramEvaluator<ScratchEvaluatePreparer,
                             DynamicCompressedRowJacobianWriter,
                             DynamicCompressedRowJacobianFinalizer>>(options,
                                                                     program);
      } else {
        return std::make_unique<
            ProgramEvaluator<BlockEvaluatePreparer, BlockJacobianWriter>>(
            options, program);
      }

    default:
      *error = "Invalid Linear Solver Type. Unable to create evaluator.";
      return nullptr;
  }
}
