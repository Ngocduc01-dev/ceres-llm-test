// u0447 – ceres::internal::Take1stOrderParts::Apply
// Trích từ include/ceres/internal/autodiff.h, dòng 283–291 (chỉ để xem, không compile)

  template <typename JetT, typename T>
  inline static void Apply(int num_outputs, JetT* output, T** jacobians) {
    if (jacobians[ParameterIdx]) {
      Take1stOrderPart<Offset, N>(num_outputs, output, jacobians[ParameterIdx]);
    }
    Take1stOrderParts<std::integer_sequence<int, Ns...>,
                      ParameterIdx + 1,
                      Offset + N>::Apply(num_outputs, output, jacobians);
  }
