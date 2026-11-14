// u0252 – ceres::implicit_cast
// Trích từ internal/ceres/casts.h, dòng 65–68 (chỉ để xem, không compile)

template <typename To, typename From>
inline To implicit_cast(typename identity_<From>::type const& f) {
  return f;
}
