// u0822 – ceres::Problem::AddResidualBlock
// Trích từ include/ceres/problem.h, dòng 231–241 (chỉ để xem, không compile)

  template <typename... Ts>
  ResidualBlockId AddResidualBlock(CostFunction* cost_function,
                                   LossFunction* loss_function,
                                   double* x0,
                                   Ts*... xs) {
    const std::array<double*, sizeof...(Ts) + 1> parameter_blocks{{x0, xs...}};
    return AddResidualBlock(cost_function,
                            loss_function,
                            parameter_blocks.data(),
                            static_cast<int>(parameter_blocks.size()));
  }
