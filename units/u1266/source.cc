// u1266 – ceres::internal::ResidualBlock::NumScratchDoublesForEvaluate
// Trích từ internal/ceres/residual_block.cc, dòng 198–215 (chỉ để xem, không compile)

int ResidualBlock::NumScratchDoublesForEvaluate() const {
  // Compute the amount of scratch space needed to store the full-sized
  // jacobians. For parameters that have no manifold no storage is needed and
  // the passed-in jacobian array is used directly. Also include space to store
  // the residuals, which is needed for cost-only evaluations.  This is slightly
  // pessimistic, since both won't be needed all the time, but the amount of
  // excess should not cause problems for the caller.
  int num_parameters = NumParameterBlocks();
  int scratch_doubles = 1;
  for (int i = 0; i < num_parameters; ++i) {
    const ParameterBlock* parameter_block = parameter_blocks_[i];
    if (parameter_block->PlusJacobian() != nullptr) {
      scratch_doubles += parameter_block->Size();
    }
  }
  scratch_doubles *= NumResiduals();
  return scratch_doubles;
}
