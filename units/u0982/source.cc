// u0982 – ceres::SizedCostFunction::SizedCostFunction<kNumResiduals, Ns...>
// Trích từ include/ceres/sized_cost_function.h, dòng 59–62 (chỉ để xem, không compile)

  SizedCostFunction() {
    set_num_residuals(kNumResiduals);
    *mutable_parameter_block_sizes() = std::vector<int32_t>{Ns...};
  }
