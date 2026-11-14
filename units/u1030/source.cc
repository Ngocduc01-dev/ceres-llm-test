// u1030 – CallbackCostFunction::CallbackCostFunction
// Trích từ internal/ceres/c_api.cc, dòng 70–80 (chỉ để xem, không compile)

  CallbackCostFunction(ceres_cost_function_t cost_function,
                       void* user_data,
                       int num_residuals,
                       int num_parameter_blocks,
                       int* parameter_block_sizes)
      : cost_function_(cost_function), user_data_(user_data) {
    set_num_residuals(num_residuals);
    for (int i = 0; i < num_parameter_blocks; ++i) {
      mutable_parameter_block_sizes()->push_back(parameter_block_sizes[i]);
    }
  }
