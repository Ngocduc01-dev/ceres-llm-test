// u0963 – ceres::internal::(anonymous)::OrderingForSparseNormalCholeskyUsingSuiteSparse
// Trích từ internal/ceres/reorder_program.cc, dòng 112–167 (chỉ để xem, không compile)

void OrderingForSparseNormalCholeskyUsingSuiteSparse(
    const LinearSolverOrderingType linear_solver_ordering_type,
    const TripletSparseMatrix& tsm_block_jacobian_transpose,
    const std::vector<ParameterBlock*>& parameter_blocks,
    const ParameterBlockOrdering& parameter_block_ordering,
    int* ordering) {
#ifdef CERES_NO_SUITESPARSE
  // "Void"ing values to avoid compiler warnings about unused parameters
  (void)linear_solver_ordering_type;
  (void)tsm_block_jacobian_transpose;
  (void)parameter_blocks;
  (void)parameter_block_ordering;
  (void)ordering;
  LOG(FATAL) << "Congratulations, you found a Ceres bug! "
             << "Please report this error to the developers.";
#else
  SuiteSparse ss;
  cholmod_sparse* block_jacobian_transpose = ss.CreateSparseMatrix(
      const_cast<TripletSparseMatrix*>(&tsm_block_jacobian_transpose));

  if (linear_solver_ordering_type == ceres::AMD) {
    if (parameter_block_ordering.NumGroups() <= 1) {
      // The user did not supply a useful ordering so just go ahead
      // and use AMD.
      ss.Ordering(block_jacobian_transpose, OrderingType::AMD, ordering);
    } else {
      // The user supplied an ordering, so use CAMD.
      std::vector<int> constraints;
      constraints.reserve(parameter_blocks.size());
      for (auto* parameter_block : parameter_blocks) {
        constraints.push_back(parameter_block_ordering.GroupId(
            parameter_block->mutable_user_state()));
      }

      // Renumber the entries of constraints to be contiguous integers
      // as CAMD requires that the group ids be in the range [0,
      // parameter_blocks.size() - 1].
      MapValuesToContiguousRange(constraints.size(), constraints.data());
      ss.ConstrainedApproximateMinimumDegreeOrdering(
          block_jacobian_transpose, constraints.data(), ordering);
    }
  } else if (linear_solver_ordering_type == ceres::NESDIS) {
    // If nested dissection is chosen as an ordering algorithm, then
    // ignore any user provided linear_solver_ordering.
    CHECK(SuiteSparse::IsNestedDissectionAvailable())
        << "Congratulations, you found a Ceres bug! "
        << "Please report this error to the developers.";
    ss.Ordering(block_jacobian_transpose, OrderingType::NESDIS, ordering);
  } else {
    LOG(FATAL) << "Congratulations, you found a Ceres bug! "
               << "Please report this error to the developers.";
  }

  ss.Free(block_jacobian_transpose);
#endif  // CERES_NO_SUITESPARSE
}
