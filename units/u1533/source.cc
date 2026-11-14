// u1533 – ceres::Solver::Solve
// Trích từ internal/ceres/solver.cc, dòng 710–830 (chỉ để xem, không compile)

void Solver::Solve(const Solver::Options& options,
                   Problem* problem,
                   Solver::Summary* summary) {
  using internal::PreprocessedProblem;
  using internal::Preprocessor;
  using internal::ProblemImpl;
  using internal::Program;
  using internal::WallTimeInSeconds;

  CHECK(problem != nullptr);
  CHECK(summary != nullptr);

  double start_time = WallTimeInSeconds();
  *summary = Summary();
  if (!options.IsValid(&summary->message)) {
    LOG(ERROR) << "Terminating: " << summary->message;
    return;
  }

  ProblemImpl* problem_impl = problem->mutable_impl();
  Program* program = problem_impl->mutable_program();
  PreSolveSummarize(options, problem_impl, summary);

#ifndef CERES_NO_CUDA
  if (IsCudaRequired(options)) {
    if (!problem_impl->context()->InitCuda(&summary->message)) {
      LOG(ERROR) << "Terminating: " << summary->message;
      return;
    }
  }
#endif  // CERES_NO_CUDA

  // If gradient_checking is enabled, wrap all cost functions in a
  // gradient checker and install a callback that terminates if any gradient
  // error is detected.
  std::unique_ptr<internal::ProblemImpl> gradient_checking_problem;
  internal::GradientCheckingIterationCallback gradient_checking_callback;
  Solver::Options modified_options = options;
  if (options.check_gradients) {
    modified_options.callbacks.push_back(&gradient_checking_callback);
    gradient_checking_problem = CreateGradientCheckingProblemImpl(
        problem_impl,
        options.gradient_check_numeric_derivative_relative_step_size,
        options.gradient_check_relative_precision,
        &gradient_checking_callback);
    problem_impl = gradient_checking_problem.get();
    program = problem_impl->mutable_program();
  }

  // Make sure that all the parameter blocks states are set to the
  // values provided by the user.
  program->SetParameterBlockStatePtrsToUserStatePtrs();

  // The main thread also does work so we only need to launch num_threads - 1.
  problem_impl->context()->EnsureMinimumThreads(options.num_threads - 1);

  auto preprocessor = Preprocessor::Create(modified_options.minimizer_type);
  PreprocessedProblem pp;

  const bool status =
      preprocessor->Preprocess(modified_options, problem_impl, &pp);

  // We check the linear_solver_options.type rather than
  // modified_options.linear_solver_type because, depending on the
  // lack of a Schur structure, the preprocessor may change the linear
  // solver type.
  if (IsSchurType(pp.linear_solver_options.type)) {
    // TODO(sameeragarwal): We can likely eliminate the duplicate call
    // to DetectStructure here and inside the linear solver, by
    // calling this in the preprocessor.
    int row_block_size;
    int e_block_size;
    int f_block_size;
    DetectStructure(*static_cast<internal::BlockSparseMatrix*>(
                         pp.minimizer_options.jacobian.get())
                         ->block_structure(),
                    pp.linear_solver_options.elimination_groups[0],
                    &row_block_size,
                    &e_block_size,
                    &f_block_size);
    summary->schur_structure_given =
        SchurStructureToString(row_block_size, e_block_size, f_block_size);
    internal::GetBestSchurTemplateSpecialization(
        &row_block_size, &e_block_size, &f_block_size);
    summary->schur_structure_used =
        SchurStructureToString(row_block_size, e_block_size, f_block_size);
  }

  summary->fixed_cost = pp.fixed_cost;
  summary->preprocessor_time_in_seconds = WallTimeInSeconds() - start_time;

  if (status) {
    const double minimizer_start_time = WallTimeInSeconds();
    Minimize(&pp, summary);
    summary->minimizer_time_in_seconds =
        WallTimeInSeconds() - minimizer_start_time;
  } else {
    summary->message = pp.error;
  }

  const double postprocessor_start_time = WallTimeInSeconds();
  problem_impl = problem->mutable_impl();
  program = problem_impl->mutable_program();
  // On exit, ensure that the parameter blocks again point at the user
  // provided values and the parameter blocks are numbered according
  // to their position in the original user provided program.
  program->SetParameterBlockStatePtrsToUserStatePtrs();
  program->SetParameterOffsetsAndIndex();
  PostSolveSummarize(pp, summary);
  summary->postprocessor_time_in_seconds =
      WallTimeInSeconds() - postprocessor_start_time;

  // If the gradient checker reported an error, we want to report FAILURE
  // instead of USER_FAILURE and provide the error log.
  if (gradient_checking_callback.gradient_error_detected()) {
    summary->termination_type = FAILURE;
    summary->message = gradient_checking_callback.error_log();
  }

  summary->total_time_in_seconds = WallTimeInSeconds() - start_time;
}
