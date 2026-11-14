// u0791 – ceres::internal::ReorderSchurComplementColumnsUsingSuiteSparse
// Trích từ internal/ceres/reorder_program.cc, dòng 339–380 (chỉ để xem, không compile)

static void ReorderSchurComplementColumnsUsingSuiteSparse(
    const ParameterBlockOrdering& parameter_block_ordering, Program* program) {
#ifdef CERES_NO_SUITESPARSE
  // "Void"ing values to avoid compiler warnings about unused parameters
  (void)parameter_block_ordering;
  (void)program;
#else
  SuiteSparse ss;
  std::vector<int> constraints;
  std::vector<ParameterBlock*>& parameter_blocks =
      *(program->mutable_parameter_blocks());

  for (auto* parameter_block : parameter_blocks) {
    constraints.push_back(parameter_block_ordering.GroupId(
        parameter_block->mutable_user_state()));
  }

  // Renumber the entries of constraints to be contiguous integers as
  // CAMD requires that the group ids be in the range [0,
  // parameter_blocks.size() - 1].
  MapValuesToContiguousRange(constraints.size(), constraints.data());

  // Compute a block sparse presentation of J'.
  std::unique_ptr<TripletSparseMatrix> tsm_block_jacobian_transpose(
      program->CreateJacobianBlockSparsityTranspose());

  cholmod_sparse* block_jacobian_transpose =
      ss.CreateSparseMatrix(tsm_block_jacobian_transpose.get());

  std::vector<int> ordering(parameter_blocks.size(), 0);
  ss.ConstrainedApproximateMinimumDegreeOrdering(
      block_jacobian_transpose, constraints.data(), ordering.data());
  ss.Free(block_jacobian_transpose);

  const std::vector<ParameterBlock*> parameter_blocks_copy(parameter_blocks);
  for (int i = 0; i < program->NumParameterBlocks(); ++i) {
    parameter_blocks[i] = parameter_blocks_copy[ordering[i]];
  }

  program->SetParameterOffsetsAndIndex();
#endif
}
