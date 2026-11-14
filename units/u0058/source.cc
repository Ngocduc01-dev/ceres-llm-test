// u0058 – ceres::internal::AsScalar
// Trích từ include/ceres/internal/jet_traits.h, dòng 111–115 (chỉ để xem, không compile)

template <typename T, int N>
constexpr decltype(auto) AsScalar(const Jet<T, N>& value) noexcept(
    noexcept(AsScalar(value.a))) {
  return AsScalar(value.a);
}
