// u0500 – ceres::CrossProduct
// Trích từ include/ceres/rotation.h, dòng 776–784 (chỉ để xem, không compile)

template <typename T>
inline void CrossProduct(const T x[3], const T y[3], T x_cross_y[3]) {
  DCHECK_NE(x, x_cross_y) << "Inplace cross product is not supported.";
  DCHECK_NE(y, x_cross_y) << "Inplace cross product is not supported.";

  x_cross_y[0] = x[1] * y[2] - x[2] * y[1];
  x_cross_y[1] = x[2] * y[0] - x[0] * y[2];
  x_cross_y[2] = x[0] * y[1] - x[1] * y[0];
}
