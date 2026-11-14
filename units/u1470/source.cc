// u1470 – ceres::internal::ReorderProgramForSchurTypeLinearSolver
// Trích từ internal/ceres/reorder_program.cc, dòng 444–538 (chỉ để xem, không compile)

bool ReorderProgramForSchurTypeLinearSolver(
    const LinearSolverType linear_solver_type,
    const SparseLinearAlgebraLibraryType sparse_linear_algebra_library_type,
    const LinearSolverOrderingType linear_solver_ordering_type,
    const ProblemImpl::ParameterMap& parameter_map,
    ParameterBlockOrdering* parameter_block_ordering,
    Program* program,
    std::string* error) {
  if (parameter_block_ordering->NumElements() !=
      program->NumParameterBlocks()) {
    *error = StringPrintf(
        "The program has %d parameter blocks, but the parameter block "
        "ordering has %d parameter blocks.",
        program->NumParameterBlocks(),
        parameter_block_ordering->NumElements());
    return false;
  }

  if (parameter_block_ordering->NumGroups() == 1) {
    // If the user supplied an parameter_block_ordering with just one
    // group, it is equivalent to the user supplying nullptr as an
    // parameter_block_ordering. Ceres is completely free to choose the
    // parameter block ordering as it sees fit. For Schur type solvers,
    // this means that the user wishes for Ceres to identify the
    // e_blocks, which we do by computing a maximal independent set.
    std::vector<ParameterBlock*> schur_ordering;
    const int size_of_first_elimination_group =
        ComputeStableSchurOrdering(*program, &schur_ordering);

    CHECK_EQ(schur_ordering.size(), program->NumParameterBlocks())
        << "Congratulations, you found a Ceres bug! Please report this error "
        << "to the developers.";

    // Update the parameter_block_ordering object.
    for (int i = 0; i < schur_ordering.size(); ++i) {
      double* parameter_block = schur_ordering[i]->mutable_user_state();
      const int group_id = (i < size_of_first_elimination_group) ? 0 : 1;
      parameter_block_ordering->AddElementToGroup(parameter_block, group_id);
    }

    // We could call ApplyOrdering but this is cheaper and
    // simpler.
    swap(*program->mutable_parameter_blocks(), schur_ordering);
  } else {
    // The user provided an ordering with more than one elimination
    // group.

    // Verify that the first elimination group is an independent set.

    // TODO(sameeragarwal): Investigate if this should be a set or an
    // unordered_set.
    const std::set<double*>& first_elimination_group =
        parameter_block_ordering->group_to_elements().begin()->second;
    if (!program->IsParameterBlockSetIndependent(first_elimination_group)) {
      *error = StringPrintf(
          "The first elimination group in the parameter block "
          "ordering of size %zd is not an independent set",
          first_elimination_group.size());
      return false;
    }

    if (!ApplyOrdering(
            parameter_map, *parameter_block_ordering, program, error)) {
      return false;
    }
  }

  program->SetParameterOffsetsAndIndex();

  const int size_of_first_elimination_group =
      parameter_block_ordering->group_to_elements().begin()->second.size();

  if (linear_solver_type == SPARSE_SCHUR) {
    if (sparse_linear_algebra_library_type == SUITE_SPARSE &&
        linear_solver_ordering_type == ceres::AMD) {
      // Preordering support for schur complement only works with AMD
      // for now, since we are using CAMD.
      //
      // TODO(sameeragarwal): It maybe worth adding pre-ordering support for
      // nested dissection too.
      ReorderSchurComplementColumnsUsingSuiteSparse(*parameter_block_ordering,
                                                    program);
    } else if (sparse_linear_algebra_library_type == EIGEN_SPARSE) {
      ReorderSchurComplementColumnsUsingEigen(linear_solver_ordering_type,
                                              size_of_first_elimination_group,
                                              parameter_map,
                                              program);
    }
  }

  // Schur type solvers also require that their residual blocks be
  // lexicographically ordered.
  return LexicographicallyOrderResidualBlocks(
      size_of_first_elimination_group, program, error);
}
