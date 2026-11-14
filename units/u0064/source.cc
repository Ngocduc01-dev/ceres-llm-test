// u0064 – ceres::internal::VariadicEvaluateImpl
// Trích từ include/ceres/internal/variadic_evaluate.h, dòng 59–66 (chỉ để xem, không compile)

template <typename Functor, typename T>
inline bool VariadicEvaluateImpl(const Functor& functor,
                                 T const* const* input,
                                 T* output,
                                 std::true_type /*is_dynamic*/,
                                 std::integer_sequence<int>) {
  return functor(input, output);
}
