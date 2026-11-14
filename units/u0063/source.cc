// u0063 – ceres::internal::VariadicEvaluateImpl
// Trích từ include/ceres/internal/variadic_evaluate.h, dòng 46–56 (chỉ để xem, không compile)

template <typename Functor, typename T, int... Indices>
inline bool VariadicEvaluateImpl(const Functor& functor,
                                 T const* const* input,
                                 T* output,
                                 std::false_type /*is_dynamic*/,
                                 std::integer_sequence<int, Indices...>) {
  static_assert(sizeof...(Indices) > 0,
                "Invalid number of parameter blocks. At least one parameter "
                "block must be specified.");
  return functor(input[Indices]..., output);
}
