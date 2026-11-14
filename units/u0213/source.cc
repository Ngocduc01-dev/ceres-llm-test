// u0213 – ceres::DotProduct
// Trích từ include/ceres/rotation.h, dòng 786–789 (chỉ để xem, không compile)

template <typename T>
inline T DotProduct(const T x[3], const T y[3]) {
  return (x[0] * y[0] + x[1] * y[1] + x[2] * y[2]);
}
