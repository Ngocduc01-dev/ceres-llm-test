// u0986 – ceres::internal::BlockEvaluatePreparer::Init
// Trích từ internal/ceres/block_evaluate_preparer.cc, dòng 43–47 (chỉ để xem, không compile)

void BlockEvaluatePreparer::Init(int const* const* jacobian_layout,
                                 int max_derivatives_per_residual_block) {
  jacobian_layout_ = jacobian_layout;
  scratch_evaluate_preparer_.Init(max_derivatives_per_residual_block);
}
