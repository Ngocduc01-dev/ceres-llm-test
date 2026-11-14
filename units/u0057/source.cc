// u0057 – ceres::internal::AsScalar
// Trích từ include/ceres/internal/jet_traits.h, dòng 104–107 (chỉ để xem, không compile)

template <typename T>
constexpr decltype(auto) AsScalar(T&& value) noexcept {
  return std::forward<T>(value);
}
