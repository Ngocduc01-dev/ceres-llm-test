// u1383 – ceres::internal::BlockJacobianWriter::CreateEvaluatePreparers
// Trích từ internal/ceres/block_jacobian_writer.cc, dòng 183–194 (chỉ để xem, không compile)

std::unique_ptr<BlockEvaluatePreparer[]>
BlockJacobianWriter::CreateEvaluatePreparers(unsigned num_threads) {
  const int max_derivatives_per_residual_block =
      program_->MaxDerivativesPerResidualBlock();

  auto preparers = std::make_unique<BlockEvaluatePreparer[]>(num_threads);
  for (unsigned i = 0; i < num_threads; i++) {
    preparers[i].Init(jacobian_layout_.data(),
                      max_derivatives_per_residual_block);
  }
  return preparers;
}
