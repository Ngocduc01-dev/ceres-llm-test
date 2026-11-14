// u1453 – ceres::internal::ReorderSchurComplementColumnsUsingEigen
// Trích từ internal/ceres/reorder_program.cc, dòng 382–442 (chỉ để xem, không compile)

static void ReorderSchurComplementColumnsUsingEigen(
    LinearSolverOrderingType ordering_type,
    const int size_of_first_elimination_group,
    const ProblemImpl::ParameterMap& /*parameter_map*/,
    Program* program) {
#if defined(CERES_USE_EIGEN_SPARSE)
  std::unique_ptr<TripletSparseMatrix> tsm_block_jacobian_transpose(
      program->CreateJacobianBlockSparsityTranspose());
  using SparseMatrix = Eigen::SparseMatrix<int>;
  const SparseMatrix block_jacobian =
      CreateBlockJacobian(*tsm_block_jacobian_transpose);
  const int num_rows = block_jacobian.rows();
  const int num_cols = block_jacobian.cols();

  // Vertically partition the jacobian in parameter blocks of type E
  // and F.
  const SparseMatrix E =
      block_jacobian.block(0, 0, num_rows, size_of_first_elimination_group);
  const SparseMatrix F =
      block_jacobian.block(0,
                           size_of_first_elimination_group,
                           num_rows,
                           num_cols - size_of_first_elimination_group);

  // Block sparsity pattern of the schur complement.
  const SparseMatrix block_schur_complement =
      F.transpose() * F - F.transpose() * E * E.transpose() * F;

  Eigen::PermutationMatrix<Eigen::Dynamic, Eigen::Dynamic, int> perm;
  if (ordering_type == ceres::AMD) {
    Eigen::AMDOrdering<int> amd_ordering;
    amd_ordering(block_schur_complement, perm);
  } else {
#ifndef CERES_NO_EIGEN_METIS
    Eigen::MetisOrdering<int> metis_ordering;
    metis_ordering(block_schur_complement, perm);
#else
    perm.setIdentity(block_schur_complement.rows());
#endif
  }

  const std::vector<ParameterBlock*>& parameter_blocks =
      program->parameter_blocks();
  std::vector<ParameterBlock*> ordering(num_cols);

  // The ordering of the first size_of_first_elimination_group does
  // not matter, so we preserve the existing ordering.
  for (int i = 0; i < size_of_first_elimination_group; ++i) {
    ordering[i] = parameter_blocks[i];
  }

  // For the rest of the blocks, use the ordering computed using AMD.
  for (int i = 0; i < block_schur_complement.cols(); ++i) {
    ordering[size_of_first_elimination_group + i] =
        parameter_blocks[size_of_first_elimination_group + perm.indices()[i]];
  }

  swap(*program->mutable_parameter_blocks(), ordering);
  program->SetParameterOffsetsAndIndex();
#endif
}
