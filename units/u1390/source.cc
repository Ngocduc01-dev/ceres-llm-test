// u1390 – ceres::internal::Program::IsValid
// Trích từ internal/ceres/program.cc, dòng 160–188 (chỉ để xem, không compile)

bool Program::IsValid() const {
  for (int i = 0; i < residual_blocks_.size(); ++i) {
    const ResidualBlock* residual_block = residual_blocks_[i];
    if (residual_block->index() != i) {
      LOG(WARNING) << "Residual block: " << i
                   << " has incorrect index: " << residual_block->index();
      return false;
    }
  }

  int state_offset = 0;
  int delta_offset = 0;
  for (int i = 0; i < parameter_blocks_.size(); ++i) {
    const ParameterBlock* parameter_block = parameter_blocks_[i];
    if (parameter_block->index() != i ||
        parameter_block->state_offset() != state_offset ||
        parameter_block->delta_offset() != delta_offset) {
      LOG(WARNING) << "Parameter block: " << i
                   << "has incorrect indexing information: "
                   << parameter_block->ToString();
      return false;
    }

    state_offset += parameter_blocks_[i]->Size();
    delta_offset += parameter_blocks_[i]->TangentSize();
  }

  return true;
}
