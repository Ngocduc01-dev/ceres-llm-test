// u0410 – ceres::internal::ScratchEvaluatePreparer::Init
// Trích từ internal/ceres/scratch_evaluate_preparer.cc, dòng 52–55 (chỉ để xem, không compile)

void ScratchEvaluatePreparer::Init(int max_derivatives_per_residual_block) {
  jacobian_scratch_ = std::make_unique<double[]>(
      static_cast<std::size_t>(max_derivatives_per_residual_block));
}
