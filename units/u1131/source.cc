// u1131 – ceres::internal::ProblemImpl::DeleteBlock
// Trích từ internal/ceres/problem_impl.cc, dòng 223–226 (chỉ để xem, không compile)

void ProblemImpl::DeleteBlock(ParameterBlock* parameter_block) {
  parameter_block_map_.erase(parameter_block->mutable_user_state());
  delete parameter_block;
}
