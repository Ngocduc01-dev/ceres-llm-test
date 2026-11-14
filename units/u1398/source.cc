// u1398 – ceres::internal::ScratchEvaluatePreparer::Create
// Trích từ internal/ceres/scratch_evaluate_preparer.cc, dòng 41–50 (chỉ để xem, không compile)

std::unique_ptr<ScratchEvaluatePreparer[]> ScratchEvaluatePreparer::Create(
    const Program& program, unsigned num_threads) {
  auto preparers = std::make_unique<ScratchEvaluatePreparer[]>(num_threads);
  int max_derivatives_per_residual_block =
      program.MaxDerivativesPerResidualBlock();
  for (unsigned i = 0; i < num_threads; i++) {
    preparers[i].Init(max_derivatives_per_residual_block);
  }
  return preparers;
}
