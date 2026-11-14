// u0975 – ceres::DynamicCostFunction::AddParameterBlock
// Trích từ include/ceres/dynamic_cost_function.h, dòng 44–46 (chỉ để xem, không compile)

  virtual void AddParameterBlock(int size) {
    mutable_parameter_block_sizes()->push_back(size);
  }
