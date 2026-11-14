// u0023 – ceres::internal::Make1stOrderPerturbations::Apply
// Trích từ include/ceres/internal/autodiff.h, dòng 218–225 (chỉ để xem, không compile)

  template <typename T, typename JetT>
  inline static void Apply(T const* const* parameters, JetT* x) {
    Make1stOrderPerturbation<0, N, Offset, T, JetT>::Apply(
        parameters[ParameterIdx], x + Offset);
    Make1stOrderPerturbations<std::integer_sequence<int, Ns...>,
                              ParameterIdx + 1,
                              Offset + N>::Apply(parameters, x);
  }
