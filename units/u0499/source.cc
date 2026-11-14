// u0499 – ceres::QuaternionProduct
// Trích từ include/ceres/rotation.h, dòng 762–773 (chỉ để xem, không compile)

template <typename T>
inline void QuaternionProduct(const T z[4], const T w[4], T zw[4]) {
  DCHECK_NE(z, zw) << "Inplace quaternion product is not supported.";
  DCHECK_NE(w, zw) << "Inplace quaternion product is not supported.";

  // clang-format off
  zw[0] = z[0] * w[0] - z[1] * w[1] - z[2] * w[2] - z[3] * w[3];
  zw[1] = z[0] * w[1] + z[1] * w[0] + z[2] * w[3] - z[3] * w[2];
  zw[2] = z[0] * w[2] - z[1] * w[3] + z[2] * w[0] + z[3] * w[1];
  zw[3] = z[0] * w[3] + z[1] * w[2] - z[2] * w[1] + z[3] * w[0];
  // clang-format on
}
