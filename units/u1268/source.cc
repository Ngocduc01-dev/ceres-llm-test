// u1268 – ceres::internal::Program::SetParameterOffsetsAndIndex
// Trích từ internal/ceres/program.cc, dòng 140–158 (chỉ để xem, không compile)

void Program::SetParameterOffsetsAndIndex() {
  // Set positions for all parameters appearing as arguments to residuals to one
  // past the end of the parameter block array.
  for (auto* residual_block : residual_blocks_) {
    for (int j = 0; j < residual_block->NumParameterBlocks(); ++j) {
      residual_block->parameter_blocks()[j]->set_index(-1);
    }
  }
  // For parameters that appear in the program, set their position and offset.
  int state_offset = 0;
  int delta_offset = 0;
  for (int i = 0; i < parameter_blocks_.size(); ++i) {
    parameter_blocks_[i]->set_index(i);
    parameter_blocks_[i]->set_state_offset(state_offset);
    parameter_blocks_[i]->set_delta_offset(delta_offset);
    state_offset += parameter_blocks_[i]->Size();
    delta_offset += parameter_blocks_[i]->TangentSize();
  }
}
