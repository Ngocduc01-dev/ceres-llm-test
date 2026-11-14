// u1460 – ceres::internal::(anonymous)::SetupLinearSolver
// Trích từ internal/ceres/trust_region_preprocessor.cc, dòng 157–257 (chỉ để xem, không compile)

bool SetupLinearSolver(PreprocessedProblem* pp) {
  Solver::Options& options = pp->options;
  pp->linear_solver_options = LinearSolver::Options();

  if (!options.linear_solver_ordering) {
    // If the user has not supplied a linear solver ordering, then we
    // assume that they are giving all the freedom to us in choosing
    // the best possible ordering. This intent can be indicated by
    // putting all the parameter blocks in the same elimination group.
    options.linear_solver_ordering =
        CreateDefaultLinearSolverOrdering(*pp->reduced_program);
  } else {
    // If the user supplied an ordering, then check if the first
    // elimination group is still non-empty after the reduced problem
    // has been constructed.
    //
    // This is important for Schur type linear solvers, where the
    // first elimination group is special -- it needs to be an
    // independent set.
    //
    // If the first elimination group is empty, then we cannot use the
    // user's requested linear solver (and a preconditioner as the
    // case may be) so we must use a different one.
    ParameterBlockOrdering* ordering = options.linear_solver_ordering.get();
    const int min_group_id = ordering->MinNonZeroGroup();
    ordering->Remove(pp->removed_parameter_blocks);
    if (IsSchurType(options.linear_solver_type) &&
        min_group_id != ordering->MinNonZeroGroup()) {
      AlternateLinearSolverAndPreconditionerForSchurTypeLinearSolver(&options);
    }
  }

  // Reorder the program to reduce fill in and improve cache coherency
  // of the Jacobian.
  if (!ReorderProgram(pp)) {
    return false;
  }

  // Configure the linear solver.
  pp->linear_solver_options.min_num_iterations =
      options.min_linear_solver_iterations;
  pp->linear_solver_options.max_num_iterations =
      options.max_linear_solver_iterations;
  pp->linear_solver_options.type = options.linear_solver_type;
  pp->linear_solver_options.preconditioner_type = options.preconditioner_type;
  pp->linear_solver_options.use_spse_initialization =
      options.use_spse_initialization;
  pp->linear_solver_options.spse_tolerance = options.spse_tolerance;
  pp->linear_solver_options.max_num_spse_iterations =
      options.max_num_spse_iterations;
  pp->linear_solver_options.visibility_clustering_type =
      options.visibility_clustering_type;
  pp->linear_solver_options.sparse_linear_algebra_library_type =
      options.sparse_linear_algebra_library_type;

  pp->linear_solver_options.dense_linear_algebra_library_type =
      options.dense_linear_algebra_library_type;
  pp->linear_solver_options.use_explicit_schur_complement =
      options.use_explicit_schur_complement;
  pp->linear_solver_options.dynamic_sparsity = options.dynamic_sparsity;
  pp->linear_solver_options.use_mixed_precision_solves =
      options.use_mixed_precision_solves;
  pp->linear_solver_options.max_num_refinement_iterations =
      options.max_num_refinement_iterations;
  pp->linear_solver_options.num_threads = options.num_threads;
  pp->linear_solver_options.context = pp->problem->context();

  if (IsSchurType(pp->linear_solver_options.type)) {
    OrderingToGroupSizes(options.linear_solver_ordering.get(),
                         &pp->linear_solver_options.elimination_groups);

    // Schur type solvers expect at least two elimination groups. If
    // there is only one elimination group, then it is guaranteed that
    // this group only contains e_blocks. Thus we add a dummy
    // elimination group with zero blocks in it.
    if (pp->linear_solver_options.elimination_groups.size() == 1) {
      pp->linear_solver_options.elimination_groups.push_back(0);
    }
  }

  if (!options.dynamic_sparsity &&
      AreJacobianColumnsOrdered(options.linear_solver_type,
                                options.preconditioner_type,
                                options.sparse_linear_algebra_library_type,
                                options.linear_solver_ordering_type)) {
    pp->linear_solver_options.ordering_type = OrderingType::NATURAL;
  } else {
    if (options.linear_solver_ordering_type == ceres::AMD) {
      pp->linear_solver_options.ordering_type = OrderingType::AMD;
    } else if (options.linear_solver_ordering_type == ceres::NESDIS) {
      pp->linear_solver_options.ordering_type = OrderingType::NESDIS;
    } else {
      LOG(FATAL) << "Congratulations you have found a bug in Ceres Solver."
                 << " Please report this to the maintainers. : "
                 << options.linear_solver_ordering_type;
    }
  }

  pp->linear_solver = LinearSolver::Create(pp->linear_solver_options);
  return (pp->linear_solver != nullptr);
}
