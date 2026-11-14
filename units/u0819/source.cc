// u0819 – ceres::internal::VariadicEvaluateImpl
// Trích từ include/ceres/internal/variadic_evaluate.h, dòng 82–88 (chỉ để xem, không compile)

template <typename ParameterDims, typename Functor, typename T>
inline bool VariadicEvaluateImpl(const Functor& functor,
                                 T const* const* input,
                                 T* output,
                                 const CostFunction* /* NOT USED */) {
  return functor.Evaluate(input, output, nullptr);
}
