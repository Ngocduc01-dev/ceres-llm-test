// u0066 – ceres::internal::VariadicEvaluate
// Trích từ include/ceres/internal/variadic_evaluate.h, dòng 102–107 (chỉ để xem, không compile)

template <typename ParameterDims, typename Functor, typename T>
inline bool VariadicEvaluate(const Functor& functor,
                             T const* const* input,
                             T* output) {
  return VariadicEvaluateImpl<ParameterDims>(functor, input, output, &functor);
}
