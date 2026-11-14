// u0559 – ceres::CostFunction::mutable_parameter_block_sizes
// Trích từ include/ceres/cost_function.h, dòng 127–129 (chỉ để xem, không compile)

  std::vector<int32_t>* mutable_parameter_block_sizes() {
    return &parameter_block_sizes_;
  }
