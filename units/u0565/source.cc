// u0565 – ceres::internal::ParameterDims::GetUnpackedParameters
// Trích từ include/ceres/internal/parameter_dims.h, dòng 82–86 (chỉ để xem, không compile)

  template <typename T, int... Indices>
  static inline std::array<T*, kNumParameterBlocks> GetUnpackedParameters(
      T* ptr, std::integer_sequence<int, Indices...>) {
    return std::array<T*, kNumParameterBlocks>{{ptr + Indices...}};
  }
