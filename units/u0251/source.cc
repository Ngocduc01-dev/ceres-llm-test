// u0251 – ceres::implicit_cast
// Trích từ internal/ceres/casts.h, dòng 58–61 (chỉ để xem, không compile)

template <typename To>
inline To implicit_cast(typename identity_<To>::type to) {
  return to;
}
