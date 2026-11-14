// u0561 – ceres::CostFunctionToFunctor::GetParameterPointers
// Trích từ include/ceres/cost_function_to_functor.h, dòng 158–164 (chỉ để xem, không compile)

  template <typename T, typename Tuple, int... Indices>
  static std::array<const T*, ParameterDims::kNumParameterBlocks>
  GetParameterPointers(const Tuple& paramPointers,
                       std::integer_sequence<int, Indices...>) {
    return std::array<const T*, ParameterDims::kNumParameterBlocks>{
        {std::get<Indices>(paramPointers)...}};
  }
