// u0014 – ceres::CostFunctionToFunctor::operator()
// Trích từ include/ceres/cost_function_to_functor.h, dòng 133–153 (chỉ để xem, không compile)

  template <typename T, typename... Ts>
  bool operator()(const T* p1, Ts*... ps) const {
    // Add one because of residual block.
    static_assert(sizeof...(Ts) + 1 == ParameterDims::kNumParameterBlocks + 1,
                  "Invalid number of parameter blocks specified.");

    auto params = std::make_tuple(p1, ps...);

    // Extract residual pointer from params. The residual pointer is the
    // last pointer.
    constexpr int kResidualIndex = ParameterDims::kNumParameterBlocks;
    T* residuals = std::get<kResidualIndex>(params);

    // Extract parameter block pointers from params.
    using Indices =
        std::make_integer_sequence<int, ParameterDims::kNumParameterBlocks>;
    std::array<const T*, ParameterDims::kNumParameterBlocks> parameter_blocks =
        GetParameterPointers<T>(params, Indices());

    return cost_functor_(parameter_blocks.data(), residuals);
  }
