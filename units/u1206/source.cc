// u1206 – ceres::TinySolverCostFunctionAdapter::TinySolverCostFunctionAdapter<kNumResiduals, kNumParameters>
// Trích từ include/ceres/tiny_solver_cost_function_adapter.h, dòng 88–105 (chỉ để xem, không compile)

  explicit TinySolverCostFunctionAdapter(const CostFunction& cost_function)
      : cost_function_(cost_function) {
    CHECK_EQ(cost_function_.parameter_block_sizes().size(), 1)
        << "Only CostFunctions with exactly one parameter blocks are allowed.";

    const int parameter_block_size = cost_function_.parameter_block_sizes()[0];
    if (NUM_PARAMETERS == Eigen::Dynamic || NUM_RESIDUALS == Eigen::Dynamic) {
      if (NUM_RESIDUALS != Eigen::Dynamic) {
        CHECK_EQ(cost_function_.num_residuals(), NUM_RESIDUALS);
      }
      if (NUM_PARAMETERS != Eigen::Dynamic) {
        CHECK_EQ(parameter_block_size, NUM_PARAMETERS);
      }

      row_major_jacobian_.resize(cost_function_.num_residuals(),
                                 parameter_block_size);
    }
  }
