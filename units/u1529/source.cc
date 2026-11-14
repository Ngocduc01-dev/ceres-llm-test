// u1529 – ceres::internal::CreateGradientCheckingProblemImpl
// Trích từ internal/ceres/gradient_checking_cost_function.cc, dòng 168–278 (chỉ để xem, không compile)

std::unique_ptr<ProblemImpl> CreateGradientCheckingProblemImpl(
    ProblemImpl* problem_impl,
    double relative_step_size,
    double relative_precision,
    GradientCheckingIterationCallback* callback) {
  CHECK(callback != nullptr);
  // We create new CostFunctions by wrapping the original CostFunction in a
  // gradient checking CostFunction. So its okay for the ProblemImpl to take
  // ownership of it and destroy it. The LossFunctions and Manifolds are reused
  // and since they are owned by problem_impl, gradient_checking_problem_impl
  // should not take ownership of it.
  Problem::Options gradient_checking_problem_options;
  gradient_checking_problem_options.cost_function_ownership = TAKE_OWNERSHIP;
  gradient_checking_problem_options.loss_function_ownership =
      DO_NOT_TAKE_OWNERSHIP;
  gradient_checking_problem_options.manifold_ownership = DO_NOT_TAKE_OWNERSHIP;
  gradient_checking_problem_options.context = problem_impl->context();

  NumericDiffOptions numeric_diff_options;
  numeric_diff_options.relative_step_size = relative_step_size;

  auto gradient_checking_problem_impl =
      std::make_unique<ProblemImpl>(gradient_checking_problem_options);

  Program* program = problem_impl->mutable_program();

  // For every ParameterBlock in problem_impl, create a new parameter block with
  // the same manifold and constancy.
  const std::vector<ParameterBlock*>& parameter_blocks =
      program->parameter_blocks();
  for (auto* parameter_block : parameter_blocks) {
    gradient_checking_problem_impl->AddParameterBlock(
        parameter_block->mutable_user_state(),
        parameter_block->Size(),
        parameter_block->mutable_manifold());

    if (parameter_block->IsConstant()) {
      gradient_checking_problem_impl->SetParameterBlockConstant(
          parameter_block->mutable_user_state());
    }

    for (int i = 0; i < parameter_block->Size(); ++i) {
      gradient_checking_problem_impl->SetParameterUpperBound(
          parameter_block->mutable_user_state(),
          i,
          parameter_block->UpperBound(i));
      gradient_checking_problem_impl->SetParameterLowerBound(
          parameter_block->mutable_user_state(),
          i,
          parameter_block->LowerBound(i));
    }
  }

  // For every ResidualBlock in problem_impl, create a new
  // ResidualBlock by wrapping its CostFunction inside a
  // GradientCheckingCostFunction.
  const std::vector<ResidualBlock*>& residual_blocks =
      program->residual_blocks();
  for (int i = 0; i < residual_blocks.size(); ++i) {
    ResidualBlock* residual_block = residual_blocks[i];

    // Build a human readable string which identifies the
    // ResidualBlock. This is used by the GradientCheckingCostFunction
    // when logging debugging information.
    std::string extra_info =
        StringPrintf("Residual block id %d; depends on parameters [", i);
    std::vector<double*> parameter_blocks;
    std::vector<const Manifold*> manifolds;
    parameter_blocks.reserve(residual_block->NumParameterBlocks());
    manifolds.reserve(residual_block->NumParameterBlocks());
    for (int j = 0; j < residual_block->NumParameterBlocks(); ++j) {
      ParameterBlock* parameter_block = residual_block->parameter_blocks()[j];
      parameter_blocks.push_back(parameter_block->mutable_user_state());
      StringAppendF(&extra_info, "%p", parameter_block->mutable_user_state());
      extra_info += (j < residual_block->NumParameterBlocks() - 1) ? ", " : "]";
      manifolds.push_back(
          problem_impl->GetManifold(parameter_block->mutable_user_state()));
    }

    // Wrap the original CostFunction in a GradientCheckingCostFunction.
    CostFunction* gradient_checking_cost_function =
        new GradientCheckingCostFunction(residual_block->cost_function(),
                                         &manifolds,
                                         numeric_diff_options,
                                         relative_precision,
                                         extra_info,
                                         callback);

    // The const_cast is necessary because
    // ProblemImpl::AddResidualBlock can potentially take ownership of
    // the LossFunction, but in this case we are guaranteed that this
    // will not be the case, so this const_cast is harmless.
    gradient_checking_problem_impl->AddResidualBlock(
        gradient_checking_cost_function,
        const_cast<LossFunction*>(residual_block->loss_function()),
        parameter_blocks.data(),
        static_cast<int>(parameter_blocks.size()));
  }

  // Normally, when a problem is given to the solver, we guarantee
  // that the state pointers for each parameter block point to the
  // user provided data. Since we are creating this new problem from a
  // problem given to us at an arbitrary stage of the solve, we cannot
  // depend on this being the case, so we explicitly call
  // SetParameterBlockStatePtrsToUserStatePtrs to ensure that this is
  // the case.
  gradient_checking_problem_impl->mutable_program()
      ->SetParameterBlockStatePtrsToUserStatePtrs();

  return gradient_checking_problem_impl;
}
