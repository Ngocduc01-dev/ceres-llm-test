// u1354 – ceres::internal::DenseJacobianWriter::Write
// Trích từ internal/ceres/dense_jacobian_writer.h, dòng 71–100 (chỉ để xem, không compile)

  void Write(int residual_id,
             int residual_offset,
             double** jacobians,
             SparseMatrix* jacobian) {
    DenseSparseMatrix* dense_jacobian = down_cast<DenseSparseMatrix*>(jacobian);
    const ResidualBlock* residual_block =
        program_->residual_blocks()[residual_id];
    const int num_parameter_blocks = residual_block->NumParameterBlocks();
    const int num_residuals = residual_block->NumResiduals();

    // Now copy the jacobians for each parameter into the dense jacobian matrix.
    for (int j = 0; j < num_parameter_blocks; ++j) {
      ParameterBlock* parameter_block = residual_block->parameter_blocks()[j];

      // If the parameter block is fixed, then there is nothing to do.
      if (parameter_block->IsConstant()) {
        continue;
      }

      const int parameter_block_size = parameter_block->TangentSize();
      ConstMatrixRef parameter_jacobian(
          jacobians[j], num_residuals, parameter_block_size);

      dense_jacobian->mutable_matrix()->block(residual_offset,
                                              parameter_block->delta_offset(),
                                              num_residuals,
                                              parameter_block_size) =
          parameter_jacobian;
    }
  }
