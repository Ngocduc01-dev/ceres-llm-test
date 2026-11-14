// u0718 – ceres::QuaternionToRotation
// Trích từ include/ceres/rotation.h, dòng 706–719 (chỉ để xem, không compile)

template <typename T, int row_stride, int col_stride>
inline void QuaternionToRotation(
    const T q[4], const MatrixAdapter<T, row_stride, col_stride>& R) {
  QuaternionToScaledRotation(q, R);

  T normalizer = q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3];
  normalizer = T(1) / normalizer;

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      R(i, j) *= normalizer;
    }
  }
}
