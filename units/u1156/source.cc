// u1156 – ceres::Problem::GetParameterBlocks
// Trích từ internal/ceres/problem.cc, dòng 183–185 (chỉ để xem, không compile)

void Problem::GetParameterBlocks(std::vector<double*>* parameter_blocks) const {
  impl_->GetParameterBlocks(parameter_blocks);
}
