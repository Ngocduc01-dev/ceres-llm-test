// u1364 – ceres::internal::Program::CreateJacobianBlockSparsityTranspose
// Trích từ internal/ceres/program.cc, dòng 434–477 (chỉ để xem, không compile)

std::unique_ptr<TripletSparseMatrix>
Program::CreateJacobianBlockSparsityTranspose(int start_residual_block) const {
  // Matrix to store the block sparsity structure of the Jacobian.
  const int num_rows = NumParameterBlocks();
  const int num_cols = NumResidualBlocks() - start_residual_block;

  std::unique_ptr<TripletSparseMatrix> tsm(
      new TripletSparseMatrix(num_rows, num_cols, 10 * num_cols));
  int num_nonzeros = 0;
  int* rows = tsm->mutable_rows();
  int* cols = tsm->mutable_cols();
  double* values = tsm->mutable_values();

  for (int c = start_residual_block; c < residual_blocks_.size(); ++c) {
    const ResidualBlock* residual_block = residual_blocks_[c];
    const int num_parameter_blocks = residual_block->NumParameterBlocks();
    ParameterBlock* const* parameter_blocks =
        residual_block->parameter_blocks();

    for (int j = 0; j < num_parameter_blocks; ++j) {
      if (parameter_blocks[j]->IsConstant()) {
        continue;
      }

      // Re-size the matrix if needed.
      if (num_nonzeros >= tsm->max_num_nonzeros()) {
        tsm->set_num_nonzeros(num_nonzeros);
        tsm->Reserve(2 * num_nonzeros);
        rows = tsm->mutable_rows();
        cols = tsm->mutable_cols();
        values = tsm->mutable_values();
      }

      const int r = parameter_blocks[j]->index();
      rows[num_nonzeros] = r;
      cols[num_nonzeros] = c - start_residual_block;
      values[num_nonzeros] = 1.0;
      ++num_nonzeros;
    }
  }

  tsm->set_num_nonzeros(num_nonzeros);
  return tsm;
}
