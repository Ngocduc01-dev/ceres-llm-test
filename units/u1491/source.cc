// u1491 – ceres::internal::ProblemImpl::Evaluate
// Trích từ internal/ceres/problem_impl.cc, dòng 585–746 (chỉ để xem, không compile)

bool ProblemImpl::Evaluate(const Problem::EvaluateOptions& evaluate_options,
                           double* cost,
                           std::vector<double>* residuals,
                           std::vector<double>* gradient,
                           CRSMatrix* jacobian) {
  if (cost == nullptr && residuals == nullptr && gradient == nullptr &&
      jacobian == nullptr) {
    return true;
  }

  // If the user supplied residual blocks, then use them, otherwise
  // take the residual blocks from the underlying program.
  Program program;
  *program.mutable_residual_blocks() =
      ((evaluate_options.residual_blocks.size() > 0)
           ? evaluate_options.residual_blocks
           : program_->residual_blocks());

  const std::vector<double*>& parameter_block_ptrs =
      evaluate_options.parameter_blocks;

  std::vector<ParameterBlock*> variable_parameter_blocks;
  std::vector<ParameterBlock*>& parameter_blocks =
      *program.mutable_parameter_blocks();

  if (parameter_block_ptrs.size() == 0) {
    // The user did not provide any parameter blocks, so default to
    // using all the parameter blocks in the order that they are in
    // the underlying program object.
    parameter_blocks = program_->parameter_blocks();
  } else {
    // The user supplied a vector of parameter blocks. Using this list
    // requires a number of steps.

    // 1. Convert double* into ParameterBlock*
    parameter_blocks.resize(parameter_block_ptrs.size());
    for (int i = 0; i < parameter_block_ptrs.size(); ++i) {
      parameter_blocks[i] = FindWithDefault(
          parameter_block_map_, parameter_block_ptrs[i], nullptr);
      if (parameter_blocks[i] == nullptr) {
        LOG(FATAL) << "No known parameter block for "
                   << "Problem::Evaluate::Options.parameter_blocks[" << i << "]"
                   << " = " << parameter_block_ptrs[i];
      }
    }

    // 2. The user may have only supplied a subset of parameter
    // blocks, so identify the ones that are not supplied by the user
    // and are NOT constant. These parameter blocks are stored in
    // variable_parameter_blocks.
    //
    // To ensure that the parameter blocks are not included in the
    // columns of the jacobian, we need to make sure that they are
    // constant during evaluation and then make them variable again
    // after we are done.
    std::vector<ParameterBlock*> all_parameter_blocks(
        program_->parameter_blocks());
    std::vector<ParameterBlock*> included_parameter_blocks(
        program.parameter_blocks());

    std::vector<ParameterBlock*> excluded_parameter_blocks;
    sort(all_parameter_blocks.begin(), all_parameter_blocks.end());
    sort(included_parameter_blocks.begin(), included_parameter_blocks.end());
    set_difference(all_parameter_blocks.begin(),
                   all_parameter_blocks.end(),
                   included_parameter_blocks.begin(),
                   included_parameter_blocks.end(),
                   back_inserter(excluded_parameter_blocks));

    variable_parameter_blocks.reserve(excluded_parameter_blocks.size());
    for (auto* parameter_block : excluded_parameter_blocks) {
      if (!parameter_block->IsConstant()) {
        variable_parameter_blocks.push_back(parameter_block);
        parameter_block->SetConstant();
      }
    }
  }

  // Setup the Parameter indices and offsets before an evaluator can
  // be constructed and used.
  program.SetParameterOffsetsAndIndex();

  Evaluator::Options evaluator_options;

  // Even though using SPARSE_NORMAL_CHOLESKY requires SuiteSparse or
  // CXSparse, here it just being used for telling the evaluator to
  // use a SparseRowCompressedMatrix for the jacobian. This is because
  // the Evaluator decides the storage for the Jacobian based on the
  // type of linear solver being used.
  evaluator_options.linear_solver_type = SPARSE_NORMAL_CHOLESKY;
  evaluator_options.num_threads = evaluate_options.num_threads;

  // The main thread also does work so we only need to launch num_threads - 1.
  context_impl_->EnsureMinimumThreads(evaluator_options.num_threads - 1);
  evaluator_options.context = context_impl_;
  evaluator_options.evaluation_callback =
      program_->mutable_evaluation_callback();
  std::unique_ptr<Evaluator> evaluator(
      new ProgramEvaluator<ScratchEvaluatePreparer,
                           CompressedRowJacobianWriter>(evaluator_options,
                                                        &program));

  if (residuals != nullptr) {
    residuals->resize(evaluator->NumResiduals());
  }

  if (gradient != nullptr) {
    gradient->resize(evaluator->NumEffectiveParameters());
  }

  std::unique_ptr<CompressedRowSparseMatrix> tmp_jacobian;
  if (jacobian != nullptr) {
    tmp_jacobian.reset(down_cast<CompressedRowSparseMatrix*>(
        evaluator->CreateJacobian().release()));
  }

  // Point the state pointers to the user state pointers. This is
  // needed so that we can extract a parameter vector which is then
  // passed to Evaluator::Evaluate.
  program.SetParameterBlockStatePtrsToUserStatePtrs();

  // Copy the value of the parameter blocks into a vector, since the
  // Evaluate::Evaluate method needs its input as such. The previous
  // call to SetParameterBlockStatePtrsToUserStatePtrs ensures that
  // these values are the ones corresponding to the actual state of
  // the parameter blocks, rather than the temporary state pointer
  // used for evaluation.
  Vector parameters(program.NumParameters());
  program.ParameterBlocksToStateVector(parameters.data());

  double tmp_cost = 0;

  Evaluator::EvaluateOptions evaluator_evaluate_options;
  evaluator_evaluate_options.apply_loss_function =
      evaluate_options.apply_loss_function;
  bool status =
      evaluator->Evaluate(evaluator_evaluate_options,
                          parameters.data(),
                          &tmp_cost,
                          residuals != nullptr ? &(*residuals)[0] : nullptr,
                          gradient != nullptr ? &(*gradient)[0] : nullptr,
                          tmp_jacobian.get());

  // Make the parameter blocks that were temporarily marked constant,
  // variable again.
  for (auto* parameter_block : variable_parameter_blocks) {
    parameter_block->SetVarying();
  }

  if (status) {
    if (cost != nullptr) {
      *cost = tmp_cost;
    }
    if (jacobian != nullptr) {
      tmp_jacobian->ToCRSMatrix(jacobian);
    }
  }

  program_->SetParameterBlockStatePtrsToUserStatePtrs();
  program_->SetParameterOffsetsAndIndex();
  return status;
}
