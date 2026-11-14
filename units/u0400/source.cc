// u0400 – ceres::internal::ProgramEvaluator::EvaluateScratch::Init
// Trích từ internal/ceres/program_evaluator.h, dòng 324–336 (chỉ để xem, không compile)

    void Init(int max_parameters_per_residual_block,
              int max_scratch_doubles_needed_for_evaluate,
              int max_residuals_per_residual_block,
              int num_parameters) {
      residual_block_evaluate_scratch =
          std::make_unique<double[]>(max_scratch_doubles_needed_for_evaluate);
      gradient = std::make_unique<double[]>(num_parameters);
      VectorRef(gradient.get(), num_parameters).setZero();
      residual_block_residuals =
          std::make_unique<double[]>(max_residuals_per_residual_block);
      jacobian_block_ptrs =
          std::make_unique<double*[]>(max_parameters_per_residual_block);
    }
