// u0883 – ceres::internal::ProblemImpl::AddResidualBlock
// Trích từ internal/ceres/problem_impl.h, dòng 89–99 (chỉ để xem, không compile)

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
