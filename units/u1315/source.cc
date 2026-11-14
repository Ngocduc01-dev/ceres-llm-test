// u1315 – ceres::internal::(anonymous)::ReorderProgram
// Trích từ internal/ceres/trust_region_preprocessor.cc, dòng 110–151 (chỉ để xem, không compile)

bool ReorderProgram(PreprocessedProblem* pp) {
  const Solver::Options& options = pp->options;
  if (IsSchurType(options.linear_solver_type)) {
    return ReorderProgramForSchurTypeLinearSolver(
        options.linear_solver_type,
        options.sparse_linear_algebra_library_type,
        options.linear_solver_ordering_type,
        pp->problem->parameter_map(),
        options.linear_solver_ordering.get(),
        pp->reduced_program.get(),
        &pp->error);
  }

  if (options.linear_solver_type == SPARSE_NORMAL_CHOLESKY &&
      !options.dynamic_sparsity) {
    return ReorderProgramForSparseCholesky(
        options.sparse_linear_algebra_library_type,
        options.linear_solver_ordering_type,
        *options.linear_solver_ordering,
        0, /* use all the rows of the jacobian */
        pp->reduced_program.get(),
        &pp->error);
  }

  if (options.linear_solver_type == CGNR &&
      options.preconditioner_type == SUBSET) {
    pp->linear_solver_options.subset_preconditioner_start_row_block =
        ReorderResidualBlocksByPartition(
            options.residual_blocks_for_subset_preconditioner,
            pp->reduced_program.get());

    return ReorderProgramForSparseCholesky(
        options.sparse_linear_algebra_library_type,
        options.linear_solver_ordering_type,
        *options.linear_solver_ordering,
        pp->linear_solver_options.subset_preconditioner_start_row_block,
        pp->reduced_program.get(),
        &pp->error);
  }

  return true;
}
