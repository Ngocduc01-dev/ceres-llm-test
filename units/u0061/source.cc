// u0061 – ceres::internal::ParameterDims::GetUnpackedParameters
// Trích từ include/ceres/internal/parameter_dims.h, dòng 74–79 (chỉ để xem, không compile)

  template <typename T>
  static inline std::array<T*, kNumParameterBlocks> GetUnpackedParameters(
      T* ptr) {
    using Offsets = ExclusiveScan<Parameters>;
    return GetUnpackedParameters(ptr, Offsets());
  }
