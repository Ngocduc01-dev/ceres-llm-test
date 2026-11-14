// u1210 – ceres::CostFunctionToFunctor::CostFunctionToFunctor<kNumResiduals, Ns...>
// Trích từ include/ceres/cost_function_to_functor.h, dòng 109–131 (chỉ để xem, không compile)

  explicit CostFunctionToFunctor(CostFunction* cost_function)
      : cost_functor_(cost_function) {
    CHECK(cost_function != nullptr);
    CHECK(kNumResiduals > 0 || kNumResiduals == DYNAMIC);

    const std::vector<int32_t>& parameter_block_sizes =
        cost_function->parameter_block_sizes();
    const int num_parameter_blocks = ParameterDims::kNumParameterBlocks;
    CHECK_EQ(static_cast<int>(parameter_block_sizes.size()),
             num_parameter_blocks);

    if (parameter_block_sizes.size() == num_parameter_blocks) {
      for (int block = 0; block < num_parameter_blocks; ++block) {
        CHECK_EQ(ParameterDims::GetDim(block), parameter_block_sizes[block])
            << "Parameter block size mismatch. The specified static parameter "
               "block dimension does not match the one from the cost function.";
      }
    }

    CHECK_EQ(accumulate(
                 parameter_block_sizes.begin(), parameter_block_sizes.end(), 0),
             ParameterDims::kNumParameters);
  }
