// u0985 – ceres::TinySolverCostFunctionAdapter::NumParameters
// Trích từ include/ceres/tiny_solver_cost_function_adapter.h, dòng 130–132 (chỉ để xem, không compile)

  int NumParameters() const {
    return cost_function_.parameter_block_sizes()[0];
  }
