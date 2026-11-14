// u0065 – ceres::internal::VariadicEvaluateImpl
// Trích từ include/ceres/internal/variadic_evaluate.h, dòng 69–79 (chỉ để xem, không compile)

template <typename ParameterDims, typename Functor, typename T>
inline bool VariadicEvaluateImpl(const Functor& functor,
                                 T const* const* input,
                                 T* output,
                                 const void* /* NOT USED */) {
  using ParameterBlockIndices =
      std::make_integer_sequence<int, ParameterDims::kNumParameterBlocks>;
  using IsDynamic = std::integral_constant<bool, ParameterDims::kIsDynamic>;
  return VariadicEvaluateImpl(
      functor, input, output, IsDynamic(), ParameterBlockIndices());
}
