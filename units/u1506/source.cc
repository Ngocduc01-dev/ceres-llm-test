// u1506 – ceres::internal::(anonymous)::SetupInnerIterationMinimizer
// Trích từ internal/ceres/trust_region_preprocessor.cc, dòng 288–336 (chỉ để xem, không compile)

bool SetupInnerIterationMinimizer(PreprocessedProblem* pp) {
  Solver::Options& options = pp->options;
  if (!options.use_inner_iterations) {
    return true;
  }

  if (pp->reduced_program->mutable_evaluation_callback()) {
    pp->error = "Inner iterations cannot be used with EvaluationCallbacks";
    return false;
  }

  // With just one parameter block, the outer iteration of the trust
  // region method and inner iterations are doing exactly the same
  // thing, and thus inner iterations are not needed.
  if (pp->reduced_program->NumParameterBlocks() == 1) {
    LOG(WARNING) << "Reduced problem only contains one parameter block."
                 << "Disabling inner iterations.";
    return true;
  }

  if (options.inner_iteration_ordering != nullptr) {
    // If the user supplied an ordering, then remove the set of
    // inactive parameter blocks from it
    options.inner_iteration_ordering->Remove(pp->removed_parameter_blocks);
    if (options.inner_iteration_ordering->NumElements() == 0) {
      LOG(WARNING) << "No remaining elements in the inner iteration ordering.";
      return true;
    }

    // Validate the reduced ordering.
    if (!CoordinateDescentMinimizer::IsOrderingValid(
            *pp->reduced_program,
            *options.inner_iteration_ordering,
            &pp->error)) {
      return false;
    }
  } else {
    // The user did not supply an ordering, so create one.
    options.inner_iteration_ordering =
        CoordinateDescentMinimizer::CreateOrdering(*pp->reduced_program);
  }

  pp->inner_iteration_minimizer =
      std::make_unique<CoordinateDescentMinimizer>(pp->problem->context());
  return pp->inner_iteration_minimizer->Init(*pp->reduced_program,
                                             pp->problem->parameter_map(),
                                             *options.inner_iteration_ordering,
                                             &pp->error);
}
