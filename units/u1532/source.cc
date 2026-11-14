// u1532 – ceres_problem_add_residual_block
// Trích từ internal/ceres/c_api.cc, dòng 138–169 (chỉ để xem, không compile)

ceres_residual_block_id_t* ceres_problem_add_residual_block(
    ceres_problem_t* problem,
    ceres_cost_function_t cost_function,
    void* cost_function_data,
    ceres_loss_function_t loss_function,
    void* loss_function_data,
    int num_residuals,
    int num_parameter_blocks,
    int* parameter_block_sizes,
    double** parameters) {
  auto* ceres_problem = reinterpret_cast<Problem*>(problem);

  auto callback_cost_function =
      std::make_unique<CallbackCostFunction>(cost_function,
                                             cost_function_data,
                                             num_residuals,
                                             num_parameter_blocks,
                                             parameter_block_sizes);

  std::unique_ptr<ceres::LossFunction> callback_loss_function;
  if (loss_function != nullptr) {
    callback_loss_function = std::make_unique<CallbackLossFunction>(
        loss_function, loss_function_data);
  }

  std::vector<double*> parameter_blocks(parameters,
                                        parameters + num_parameter_blocks);
  return reinterpret_cast<ceres_residual_block_id_t*>(
      ceres_problem->AddResidualBlock(callback_cost_function.release(),
                                      callback_loss_function.release(),
                                      parameter_blocks));
}
