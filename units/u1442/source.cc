// u1442 – ceres::internal::ReorderProgramForSparseCholesky
// Trích từ internal/ceres/reorder_program.cc, dòng 540–595 (chỉ để xem, không compile)

bool ReorderProgramForSparseCholesky(
    const SparseLinearAlgebraLibraryType sparse_linear_algebra_library_type,
    const LinearSolverOrderingType linear_solver_ordering_type,
    const ParameterBlockOrdering& parameter_block_ordering,
    int start_row_block,
    Program* program,
    std::string* error) {
  if (parameter_block_ordering.NumElements() != program->NumParameterBlocks()) {
    *error = StringPrintf(
        "The program has %d parameter blocks, but the parameter block "
        "ordering has %d parameter blocks.",
        program->NumParameterBlocks(),
        parameter_block_ordering.NumElements());
    return false;
  }

  // Compute a block sparse presentation of J'.
  std::unique_ptr<TripletSparseMatrix> tsm_block_jacobian_transpose(
      program->CreateJacobianBlockSparsityTranspose(start_row_block));

  std::vector<int> ordering(program->NumParameterBlocks(), 0);
  std::vector<ParameterBlock*>& parameter_blocks =
      *(program->mutable_parameter_blocks());

  if (sparse_linear_algebra_library_type == SUITE_SPARSE) {
    OrderingForSparseNormalCholeskyUsingSuiteSparse(
        linear_solver_ordering_type,
        *tsm_block_jacobian_transpose,
        parameter_blocks,
        parameter_block_ordering,
        ordering.data());
  } else if (sparse_linear_algebra_library_type == ACCELERATE_SPARSE) {
    // Accelerate does not provide a function to perform reordering without
    // performing a full symbolic factorisation.  As such, we have nothing
    // to gain from trying to reorder the problem here, as it will happen
    // in AppleAccelerateCholesky::Factorize() (once) and reordering here
    // would involve performing two symbolic factorisations instead of one
    // which would have a negative overall impact on performance.
    return true;

  } else if (sparse_linear_algebra_library_type == EIGEN_SPARSE) {
    OrderingForSparseNormalCholeskyUsingEigenSparse(
        linear_solver_ordering_type,
        *tsm_block_jacobian_transpose,
        ordering.data());
  }

  // Apply ordering.
  const std::vector<ParameterBlock*> parameter_blocks_copy(parameter_blocks);
  for (int i = 0; i < program->NumParameterBlocks(); ++i) {
    parameter_blocks[i] = parameter_blocks_copy[ordering[i]];
  }

  program->SetParameterOffsetsAndIndex();
  return true;
}
